#include <algorithm>
#include <iostream>
struct Team {
  Team() = default;
  Team(const unsigned int &new_id, const unsigned int &new_solved_tasks, const unsigned int &new_penalty_time)
      : id(new_id + 1), solved_tasks_amount(new_solved_tasks), penalty_time(new_penalty_time) {
  }
  unsigned int id;
  unsigned int solved_tasks_amount;
  unsigned int penalty_time;
};

struct Compare {
  bool operator()(Team first, Team second) {
    if (first.solved_tasks_amount < second.solved_tasks_amount) {
      return false;
    }
    if (first.solved_tasks_amount > second.solved_tasks_amount) {
      return true;
    }

    if (first.penalty_time > second.penalty_time) {
      return false;
    }
    if (first.penalty_time < second.penalty_time) {
      return true;
    }

    if (first.id > second.id) {
      return false;
    }
    if (first.id < second.id) {
      return true;
    }
    return false;
  }
};

int main() {
  using std::cin;
  using std::cout;
  unsigned int n = 0;
  cin >> n;
  Team *team_list = new Team[n];
  for (unsigned int i = 0; i < n; ++i) {
    unsigned int amount_of_tasks = 0;
    unsigned int penalty_time = 0;
    cin >> amount_of_tasks >> penalty_time;
    team_list[i] = Team(i, amount_of_tasks, penalty_time);
  }
  std::sort(team_list, team_list + n, Compare());
  for (unsigned i = 0; i < n; ++i) {
    cout << team_list[i].id << '\n';
  }
  delete[] team_list;
}