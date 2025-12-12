#include "scheduler.hpp"
#include <vector>
#include <algorithm>

// Simple round-robin and priority scheduler implementation
class RoundRobinScheduler : public IScheduler {
    std::vector<int> order;
    size_t idx = 0;

public:
    int pick_next(const std::map<int, std::shared_ptr<Task>>& tasks, int last_run) override {
        order.clear();
            for (auto &p : tasks)
                if (p.second->state == TaskState::Ready)
                    order.push_back(p.first);
            if (order.empty())
                return -1;
            if (last_run != -1) {
                auto it = std::find(order.begin(), order.end(), last_run);
                if (it != order.end()) {
                    idx = (std::distance(order.begin(), it) + 1) % order.size();
                } else {
                    idx = 0;
                }
            } else {
                idx %= order.size();
            }

            int chosen = order[idx];
            idx = (idx + 1) % order.size();
            return chosen;
        }
}

class PriorityScheduler : public IScheduler {
public:
    int pick_next(const std::map<int, std::shared_ptr<Task>>& tasks, int) override {
        int best = -1;
        int best_prio = std::numeric_limits<int>::min();
        for (auto &p : tasks) {
            auto &t = p.second;
            if (t->state == TaskState::Ready) {
                if (t->priority > best_prio) {
                    best_prio = t->priority;
                    best = t->id;
                }
            }
        }
        return best;
    }
};

// Factory helpers (simple)
std::unique_ptr<IScheduler> make_round_robin() {
    return std::unique_ptr<IScheduler>(new RoundRobinScheduler());
}

std::unique_ptr<IScheduler> make_priority() {
    return std::unique_ptr<IScheduler>(new PriorityScheduler());
}