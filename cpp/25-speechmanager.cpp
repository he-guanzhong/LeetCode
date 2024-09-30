#include <algorithm>
#include <ctime>
#include <deque>
#include <fstream>
#include <iostream>
#include <map>
#include <numeric>
#include <vector>
using namespace std;
// 演讲比赛，12人参加，分两组，每组6个人
// 预选赛随机抽签顺序比赛，10个评委打分，去掉最低和最高取平均。前三晋级。
// 决赛6个人，前三名胜出。每轮比赛后都要现实晋级信息
// 程序功能：开始演讲（用户按任意键开始演讲），查看记录（查看之前前三名结果，csv文件）
// 程序功能：清空比赛记录，退出程序
class Speaker {
 public:
  Speaker() {}
  Speaker(string name, int ID) {
    m_name = name;
    m_ID = ID;
    m_score[0] = 0;
    m_score[1] = 0;
  }
  string m_name;
  double m_score[2];  // 2轮成绩都要记录
  int m_ID;
};

class SpeechManager {
 public:
  SpeechManager() {
    this->initSpeech();
    this->createSpeeker();
    this->loadRecord();
  }
  ~SpeechManager() {}

  void showMenu() {
    cout << "是否开始演讲" << endl;
    cout << "1.开始演讲  2.查看记录  3.清除记录  4.退出" << endl;
  }
  void exitSystem() {
    cout << "确定要退出？" << endl;
    bool select = 0;
    cin >> select;
    if (select) {
      cout << "欢迎下次使用" << endl;
      system("pause");
      exit(0);
    }
    system("cls");
  }
  void initSpeech() {
    v1.clear();
    v2.clear();
    v3.clear();
    m_Speaker.clear();
    m_Record.clear();
    m_Recordv.clear();
    m_index = 1;
  }
  void createSpeeker() {
    string nameSeed = "ABCDEFGHIJKL";
    for (int i = 0; i < nameSeed.size(); i++) {
      string name = "选手";
      name += nameSeed[i];
      int id = 101 + i;
      Speaker person(name, id);
      v1.push_back(id);
      m_Speaker.insert(make_pair(id, person));
    }
  }
  void startSpeech() {
    for (int i = 0; i < 2; i++) {
      m_index = i + 1;  // 实时更新轮次
      this->speechDraw();
      this->speechMatch();
      this->showScore();
    }
    this->saveRecord();
    // 比赛后重置比赛，防止比赛后不记录
    this->initSpeech();
    this->createSpeeker();
    this->loadRecord();
  }
  void speechDraw() {
    cout << "第" << m_index << "轮抽签，结果如下" << endl;
    if (this->m_index == 1) {
      random_shuffle(v1.begin(), v1.end());
      for_each(v1.begin(), v1.end(), [](int val) { cout << val << " "; });
      cout << endl;
    } else if (this->m_index == 2) {
      random_shuffle(v2.begin(), v2.end());
      for_each(v2.begin(), v2.end(), [](int val) { cout << val << " "; });
      cout << endl;
    }
    cout << endl;
    system("pause");
    cout << endl;
  }

  void speechMatch() {
    cout << "-------第" << this->m_index << "轮比赛正式开始！-------" << endl;
    vector<int> v;                                      // 即将处理的信息
    int num = 0;                                        // 已处理的人头数
    multimap<double, int, greater<double>> groupScore;  // 存放小组信息
    if (m_index == 1)
      v = v1;
    else if (m_index == 2)
      v = v2;
    for (vector<int>::iterator it = v.begin(); it != v.end(); it++) {
      num++;
      deque<double> scores;
      for (int j = 0; j < 10; j++) {  // 10个评委打分
        double s = rand() % 10 + 1;
        scores.push_back(s);
      }
      sort(scores.begin(), scores.end(), greater<double>());  // 降序排列
      scores.pop_back();                                      // 去掉最低分
      scores.pop_front();                                     // 去掉最高分
      m_Speaker[(*it)].m_score[m_index - 1] =  // id对应的该轮分数
          accumulate(scores.begin(), scores.end(), 0) / (double)scores.size();
      groupScore.insert(  // 保存 分数+ id
          make_pair(m_Speaker[(*it)].m_score[m_index - 1], (*it)));

      if (num % 6 == 0) {  // 首次成组
        cout << "第" << num / 6 << "轮比赛成绩" << endl;
        for (multimap<double, int, greater<double>>::iterator ii =
                 groupScore.begin();
             ii != groupScore.end(); ii++) {
          cout << ii->second << " " << m_Speaker[ii->second].m_name
               << ". 成绩为 " << ii->first << endl;
        }
        int cnt = 0;  // 提取前三名成绩
        for (multimap<double, int, greater<double>>::iterator ii =
                 groupScore.begin();
             ii != groupScore.end() && cnt < 3; ii++, cnt++) {
          if (m_index == 1)
            v2.push_back(ii->second);
          else if (m_index == 2)
            v3.push_back(ii->second);
        }
        groupScore.clear();  // 一组比完后清空
      }
    }
    cout << "第" << m_index << "轮比赛完毕" << endl;
    system("pause");
  }

  void showScore() {
    vector<int> v;  // 即将处理信息
    if (m_index == 1) {
      v = v2;
      cout << "晋级选手如下" << endl;
    } else if (m_index == 2) {
      v = v3;
      cout << "获奖选手如下" << endl;
    }
    for (vector<int>::iterator it = v.begin(); it != v.end(); it++) {
      cout << "编号 " << (*it) << " " << m_Speaker[(*it)].m_name << "  成绩 "
           << m_Speaker[(*it)].m_score[m_index - 1] << endl;
    }
    system("pause");
    this->showMenu();
  }

  void saveRecord() {
    ofstream ofs;
    ofs.open("25-speechmanager.csv", ios::out | ios::app);  // 以追加方式填写
    for (vector<int>::iterator it = v3.begin(); it != v3.end();
         it++) {  // csv格式要求行列按照","来做区分
      ofs << "姓名：," << m_Speaker[(*it)].m_name << ",编号：," << *it
          << ",成绩：," << m_Speaker[(*it)].m_score[1] << "," << endl;
    }
    ofs << endl;
    ofs.close();
    cout << " 记录已保存， 本届比赛结束 " << endl;
    fileEmpty = false;
    system("pause");
  }

  void loadRecord() {
    ifstream ifs;
    ifs.open("25-speechmanager.csv", ios::in);
    if (!ifs.is_open()) {
      cout << "文件不存在" << endl;
      ifs.close();
      fileEmpty = true;
      system("pause");
      return;
    }
    char ch;  // 要排除空文件的影响，要先看首字母是否已经是结束
    ifs >> ch;
    if (ifs.eof()) {  // 如果读到文件尾
      cout << "文件为空" << endl;
      fileEmpty = true;
      ifs.close();
      system("pause");
      return;
    }
    fileEmpty = false;  // 文件不为空现设标志位
    ifs.putback(ch);  // 把读走的字符再放回来，否则少一个字符
    string data;
    int index = 0;  // 记录第几届
    int n = 0;      // 记录行数
    while (ifs >> data) {
      int pos = -1;  // 找到的起始位置
      int start = 0;
      while (true) {
        pos = data.find(",", start);
        if (pos == -1)
          break;                                       // 没找到
        string tmp = data.substr(start, pos - start);  // 找到字符串
        m_Recordv.push_back(tmp);
        start = pos + 1;
      }
      m_Record.insert(make_pair(index, m_Recordv));
      n++;  // 读完一行增加衣阿华那个
      if (n % 3 == 0)
        index++;          // 每三行增加一届
      m_Recordv.clear();  // 没做完一次要清空
    }
    ifs.close();
  }

  void showRecord() {
    if (fileEmpty == true)
      cout << "文件不存在" << endl;
    multimap<int, vector<string>>::iterator it = m_Record.begin();
    int n = 1;
    while (it != m_Record.end()) {
      if (n % 3 == 1)
        cout << (*it).first << "届冠军姓名：" << it->second[1] << " 编号："
             << it->second[3] << " 成绩：" << it->second[5] << endl;
      else if (n % 3 == 2)
        cout << (*it).first << "届亚军姓名：" << it->second[1] << " 编号："
             << it->second[3] << " 成绩：" << it->second[5] << endl;
      else if (n % 3 == 0)
        cout << (*it).first << "届季军姓名：" << it->second[1] << " 编号："
             << it->second[3] << " 成绩：" << it->second[5] << endl;
      n++;
      it++;
    }
    system("pause");
  }

  void clearRecord() {
    cout << "确认清空？" << endl;
    bool oper;
    cin >> oper;
    if (oper) {
      if (fileEmpty) {
        cout << "已经为空" << endl;
        system("pause");
        return;
      } else {
        ofstream ofs;
        ofs.open("25-speechmanager.csv", ios::trunc);
        fileEmpty = true;
        ofs.close();
        this->initSpeech();
        this->createSpeeker();
        cout << "清空成功" << endl;
      }
    }
    system("pause");
  }

  vector<int> v1;  // 只存编号
  vector<int> v2;
  vector<int> v3;
  map<int, Speaker> m_Speaker;  // 存放编号和对应选手
  int m_index;                  // 抽签轮数
  bool fileEmpty;
  multimap<int, vector<string>> m_Record;  // 存储往届记录容器
  vector<string> m_Recordv;                // 存储读到信息的容器
};

int main() {
  srand((unsigned int)time(NULL));
  SpeechManager sm;
  int choice = 0;
  while (1) {
    sm.showMenu();
    cout << "请选择" << endl;
    cin >> choice;
    switch (choice) {
      case 1:
        sm.startSpeech();
        break;
      case 2:
        sm.showRecord();
        break;
      case 3:
        sm.clearRecord();
        break;
      case 4:
        sm.exitSystem();
        break;
      default:
        system("cls");
    }
  }
  system("pause");
  return 0;
}