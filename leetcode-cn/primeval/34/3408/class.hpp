#include "headers.h"

class TaskManager {
private:
    struct Node {
        int user_id_;
        int task_id_;
        int priority_;
    };

    std::vector<Node> line_{1};
    unsigned int top_ = 1;
    std::unordered_map<int, int> hash_table_;

    void push_heap(int lhs, int rhs) {
        int cur = rhs;
        for (int i = rhs / 2; i >= lhs; i /= 2) {
            if (comp(line_[cur], line_[i])) {
                std::swap(line_[cur], line_[i]);
                hash_table_[line_[cur].task_id_] = cur;
                hash_table_[line_[i].task_id_] = i;
                cur = i;
            } else {
                break;
            }
        }
    }

    void pop_heap(int lhs, int rhs) {
        int cur = lhs;
        Node tmp = line_[cur];
        while (cur <= rhs) {
            int l_index = cur * 2;
            int r_index = cur * 2 + 1;
            if (l_index > rhs) {
                break;
            }
            int k = l_index;
            if (r_index <= rhs && !comp(line_[l_index], line_[r_index])) {
                ++k;
            }
            line_[cur] = line_[k];
            hash_table_[line_[cur].task_id_] = cur;
            cur = k;
        }
        line_[cur] = tmp;
        hash_table_[line_[cur].task_id_] = cur;

        push_heap(lhs, cur);
    }

    static bool comp(const Node& lhs, const Node& rhs) {
        if (lhs.priority_ == rhs.priority_) {
            return lhs.task_id_ > rhs.task_id_;
        }
        return lhs.priority_ > rhs.priority_;
    }

    static bool revert_comp(const Node& lhs, const Node& rhs) {
        return !comp(lhs, rhs);
    }

public:
    explicit TaskManager(const std::vector<std::vector<int>>& tasks) {
        for (const auto& task : tasks) {
            add(task[0], task[1], task[2]);
        }
    }

    void add(int userId, int taskId, int priority) {
        if (top_ == line_.size()) {
            line_.resize(top_ + 1);
        }
        line_[top_] = {userId, taskId, priority};
        hash_table_[taskId] = top_;
        push_heap(1, top_);
        ++top_;
    }

    void edit(int taskId, int newPriority) {
        int index = hash_table_[taskId];
        Node tmp = line_[index];
        rmv(taskId);
        add(tmp.user_id_, tmp.task_id_, newPriority);
    }

    void rmv(int taskId) {
        int lhs = hash_table_[taskId];
        std::swap(line_[lhs], line_[top_ - 1]);
        hash_table_[line_[lhs].task_id_] = lhs;
        hash_table_[line_[top_ - 1].task_id_] = top_ - 1;
        // 这一步很关键, 保证 lhs 往上是个合法的堆
        push_heap(1, lhs);
        --top_;
        pop_heap(lhs, top_ - 1);
        hash_table_.erase(taskId);
    }

    int execTop() {
        if (top_ == 1) {
            return -1;
        }
        int result = line_[1].user_id_;
        rmv(line_[1].task_id_);
        return result;
    }
};
