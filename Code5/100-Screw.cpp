#include <cmath>
#include <iostream>

using namespace std;

double calcFlexibility(double clamp_d_h,
                       double clamp_D_A,
                       double clamp_l_k,
                       double d_W,
                       int E_clamp) {
  double d_wm1 = (clamp_D_A + d_W) / 2.0;
  double beta_L1 = clamp_l_k / d_wm1;
  double y1 = clamp_D_A / d_wm1;
  double tanPhai1 = 0.362 + 0.032 * log(beta_L1 / 2) + 0.153 * log(y1);
  double D_Agr1 = d_wm1 + 1 * clamp_l_k * tanPhai1;
  double delta_P11 = ((2.0 / 1.0 / clamp_d_h / tanPhai1) *
                          log((d_wm1 + clamp_d_h) * (clamp_D_A - clamp_d_h) /
                              (d_wm1 - clamp_d_h) / (clamp_D_A + clamp_d_h)) +
                      4 / (pow(clamp_D_A, 2) - pow(clamp_d_h, 2)) *
                          (clamp_l_k - (clamp_D_A - d_wm1) / 1.0 / tanPhai1)) /
                     E_clamp / M_PI / 1000;
  double delta_P12 =
      2 *
      log((d_wm1 + clamp_d_h) * (d_wm1 + 1 * clamp_l_k * tanPhai1 - clamp_d_h) /
          (d_wm1 - clamp_d_h) /
          (d_wm1 + 1 * clamp_l_k * tanPhai1 + clamp_d_h)) /
      (1 * E_clamp * M_PI * clamp_d_h * tanPhai1) / 1000;
  double delta_P1 = D_Agr1 > clamp_D_A ? delta_P11 : delta_P12;
  return delta_P1;
}

inline double calcTempF(double delta_T,
                        double clamp_l_k,
                        double alpha_screw,
                        double alpha_clamp,
                        double delta_S,
                        double delta_P,
                        double E_screw,
                        double E_screw_LT,
                        double E_clamp,
                        double E_clamp_LT) {
  double delta_F_Vth =
      -clamp_l_k * (alpha_screw * delta_T - alpha_clamp * delta_T) /
      (delta_S * E_screw / E_screw_LT + delta_P * E_clamp / E_clamp_LT) / 1e5;
  return delta_F_Vth;
}

int main() {
  // basic info
  double screw_grade = 10.9;
  int tensile_screw = (int)screw_grade * 100;
  int yield_screw = tensile_screw * (screw_grade - (int)screw_grade);
  tensile_screw = 1040;
  yield_screw = 940;
  double l_s = 203;
  double l_l = 143;
  double l_Gew = 34.8;
  double Pitch = 1.25;
  double H_thread = sqrt(3) / 2.0 * Pitch;
  double d_W = 17.0;
  double d = 8.0;
  double d1 = d - 5.0 / 4.0 * H_thread;
  double d2 = d - 3.0 / 4.0 * H_thread;
  double d3 = d1 - H_thread / 6.0;
  double d_T = 7.188;
  double d_s = (d2 + d3) / 2.0;     // 应力直径
  double d_0 = std::min(d_T, d_s);  // 最小应力直径
  double A_d3 = M_PI * std::pow(d3, 2) / 4;
  double A_l = M_PI * std::pow(d_T, 2) / 4;
  double A_N = M_PI * std::pow(d, 2) / 4;
  double A_S = M_PI * std::pow((d2 + d3), 2) / 16;

  // material
  int E_screw = 209;
  int E_clamp1 = 69;
  int E_clamp2 = 69;
  int E_screw_LT = 204;
  int E_clamp1_LT = E_clamp1;
  int E_clamp2_LT = E_clamp2;
  double alpha_screw = 1.14;   // 10e-5 /K
  double alpha_clamp1 = 2.21;  // 10e-5 /K
  double alpha_clamp2 = 2.35;  // 10e-5 /K
  int temperature_high = 140;
  int temperature_low = -40;
  int temperature_normal = 25;
  int delta_T_high = temperature_high - temperature_normal;
  int delta_T_low = temperature_normal - temperature_low;

  // clamp info
  double clamp1_d_h = 11;
  double clamp1_D_A = 20;
  double clamp1_l_k = 26;
  double clamp1_A_Pmin =
      M_PI / 4 * (std::pow(d_W, 2) - std::pow(clamp1_d_h, 2));
  double clamp1_tensile = 210;
  double clamp2_d_h = 9.5;
  double clamp2_D_A = 16;
  double clamp2_l_k = 151.8;
  double clamp2_A_Pmin = M_PI / 4 *
                         (std::pow(std::min(clamp1_D_A, clamp2_D_A), 2) -
                          std::pow(std::max(clamp1_d_h, clamp2_d_h), 2));
  double l_k = clamp1_l_k + clamp2_l_k;
  double tensile_nut = 220;

  // input
  double u_normal = 0.15;
  double u_lower = 0.12;
  double u_upper = 0.18;
  double T_normal = 40;
  double T_lower = 38;
  double T_upper = 42;

  // vibration loss
  double F_Q = 0;
  double F_A = 10834;
  double alpha_A = 1.5;

  // seal loss
  double F_kert = 1571;

  // flexibility screw
  double delta_sk = 0.4 * d / E_screw / A_N / 1000;
  double delta_l = l_l / E_screw / A_l / 1000;
  double delta_Gew = l_Gew / E_screw / A_d3 / 1000;
  double delta_G = 0.5 * d / E_screw / A_d3 / 1000;
  double delta_M = 0.33 * d / E_screw / A_N / 1000;
  double delta_S = delta_sk + delta_l + delta_Gew + delta_G + delta_M;
  cout << "delta S " << delta_S << endl;

  // flexibility clamp
  double delta_P1 =
      calcFlexibility(clamp1_d_h, clamp1_D_A, clamp1_l_k, d_W, E_clamp1);
  double delta_P2 =
      calcFlexibility(clamp2_d_h, clamp2_D_A, clamp2_l_k, clamp1_D_A, E_clamp2);
  double delta_P = delta_P1 + delta_P2;
  cout << "delta P " << delta_P << endl;

  // embedding loss
  double phai_K = delta_P / (delta_P + delta_S);
  double l_a = 0;
  double a_k = clamp1_D_A / 2;
  double n = 0.14;
  double phai_n = phai_K * n;
  double f_z = 0.01;
  double F_z = f_z / (delta_P + delta_S);
  cout << "F_Z " << F_z << endl;

  // temperature loss
  double delta_F_Vth1_LT =
      calcTempF(delta_T_low, clamp1_l_k, alpha_screw, alpha_clamp1, delta_S,
                delta_P, E_screw, E_screw_LT, E_clamp1, E_clamp1_LT);
  double delta_F_Vth2_LT =
      calcTempF(delta_T_low, clamp2_l_k, alpha_screw, alpha_clamp2, delta_S,
                delta_P, E_screw, E_screw_LT, E_clamp2, E_clamp2_LT);
  double delta_F_Vth1_HT =
      calcTempF(delta_T_high, clamp1_l_k, alpha_screw, alpha_clamp1, delta_S,
                delta_P, E_screw, E_screw_LT, E_clamp1, E_clamp1_LT);
  double delta_F_Vth2_HT =
      calcTempF(delta_T_high, clamp2_l_k, alpha_screw, alpha_clamp2, delta_S,
                delta_P, E_screw, E_screw_LT, E_clamp2, E_clamp2_LT);

  double delta_F_Vth_LT = delta_F_Vth1_LT + delta_F_Vth2_LT;
  double delta_F_Vth_HT = delta_F_Vth1_HT + delta_F_Vth2_HT;
  double F_Ultra = F_Q + delta_F_Vth_LT;
  double F_Amax = F_A + F_Q;
  double F_min = F_kert + (1 - phai_n) * F_Amax + F_z + delta_F_Vth_LT;
  double F_max = F_min * alpha_A;
  cout << "delta_F_Vth_HT " << delta_F_Vth_HT << endl;

  // max force is over?
  double v = 0.9;
  double sigma_red_Mzul = v * yield_screw;
  double F_Mzul =
      pow(d_0, 2) * M_PI / 4.0 * sigma_red_Mzul /
      (sqrt(1 + 3 * pow(1.5 * d2 / d_0 * (Pitch / M_PI / d2 + 1.155 * u_lower),
                        2)));
  double F_Smax = F_Mzul + phai_n * F_Amax;
  double sigma_Zmax = F_Smax / A_S;
  double M_G = F_Mzul * d2 / 2 * (Pitch / M_PI / d2 + 1.155 * u_lower);
  double W_p = M_PI * pow(d2 / 2 + d3 / 2, 3) / 16;
  double tau_max = M_G / W_p;
  double k_tau = 0.5;
  double sigma_redB = sqrt(pow(sigma_Zmax, 2) + 3 * pow(k_tau * tau_max, 2));
  double S_F = yield_screw / sigma_redB;
  cout << "MaxPreload: \t " << S_F << endl;

  // fatigue
  double sigma_a = (delta_F_Vth_LT + F_A * phai_n) / 2 / A_S;
  double sigma_ASV = 0.85 * (150 / d + 45);
  double S_P = sigma_ASV / sigma_a;
  cout << "Fatigue: \t " << S_P << endl;

  // surface pressure
  double A_Pmin = M_PI / 4 * (pow(d_W, 2) - pow(clamp1_d_h, 2));
  double P_Mmax = F_Mzul / A_Pmin;
  double S_Psurface = clamp1_tensile * 1.24 / P_Mmax;
  cout << "Surface: \t " << S_Psurface << endl;

  // thread length
  double tau_bmin = 0.7 * tensile_nut;
  double M_eff =
      (tensile_screw * 1.2 * A_S * Pitch) /
          (1 * 1 * tau_bmin *
           (Pitch / 2 + ((d - 0.208 * 2) - (d2 + 0.118 * 2)) * 1 / sqrt(3)) *
           M_PI * d) +
      0.8 * Pitch;
  double m_vorheff = l_s - l_k - (d - d3) / 2 - 0.8 * Pitch;
  double S_L = m_vorheff / M_eff;
  cout << "Length: \t " << S_L << endl;

  // tightening coefficient
  double D_e = 2.0 / 3.0 * (pow(d_W, 3) - pow(clamp1_d_h, 3)) /
               (pow(d_W, 2) - pow(clamp1_d_h, 2));
  double F_lower =
      T_lower / (0.159 * Pitch + 0.577 * u_upper * d2 + 0.5 * u_upper * D_e);
  double F_normal =
      T_normal / (0.159 * Pitch + 0.577 * u_normal * d2 + 0.5 * u_normal * D_e);
  double F_upper =
      T_upper / (0.159 * Pitch + 0.577 * u_lower * d2 + 0.5 * u_lower * D_e);
  cout << "F lower " << F_upper << endl;

  return 0;
}