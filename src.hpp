
#ifndef _SJTU_CPP_FINAL_SRC_HPP_
#define _SJTU_CPP_FINAL_SRC_HPP_

#include "cpu.hpp"

namespace sjtu {

    // FCFS method based CPU.
    class CPU_FCFS : public CPU {
    public:
        CPU_FCFS() : CPU() {}

        // In FCFS, we execute tasks in the order they arrive
        pair<CPUState, uint> run() override {
            // If there are no tasks, CPU is idle
            if (tasks.empty()) {
                state = idle;
                return make_pair(idle, 0);
            }

            // Find the first task in the list (oldest task)
            Task& current_task = tasks[0];
            
            // Execute one time unit of the task
            current_task.time--;
            
            // If the task is completed, remove it from the list
            if (current_task.time == 0) {
                tasks.erase(tasks.begin());
            }
            
            // CPU is busy executing this task
            state = busy;
            return make_pair(busy, current_task.task_id);
        }
    };

    // SRTF method based CPU.
    class CPU_SRTF : public CPU {
    public:
        CPU_SRTF() : CPU() {}

        // In SRTF, we execute the task with the shortest remaining time
        pair<CPUState, uint> run() override {
            // If there are no tasks, CPU is idle
            if (tasks.empty()) {
                state = idle;
                return make_pair(idle, 0);
            }

            // Find the task with the shortest remaining time
            // If there are ties, choose the one that arrived first (earlier in the vector)
            int best_idx = 0;
            uint min_time = tasks[0].time;
            
            for (int i = 1; i < tasks.size(); i++) {
                if (tasks[i].time < min_time) {
                    min_time = tasks[i].time;
                    best_idx = i;
                }
            }
            
            Task& current_task = tasks[best_idx];
            
            // Execute one time unit of the task
            current_task.time--;
            
            // If the task is completed, remove it from the list
            if (current_task.time == 0) {
                tasks.erase(tasks.begin() + best_idx);
            }
            
            // CPU is busy executing this task
            state = busy;
            return make_pair(busy, current_task.task_id);
        }
    };

    // priority method based CPU.
    class CPU_PRIORITY : public CPU {
    public:
        CPU_PRIORITY() : CPU() {}

        // In Priority scheduling, we execute the task with the highest priority (lowest priority value)
        pair<CPUState, uint> run() override {
            // If there are no tasks, CPU is idle
            if (tasks.empty()) {
                state = idle;
                return make_pair(idle, 0);
            }

            // Find the task with the highest priority (lowest priority value)
            // If there are ties, choose the one that arrived first (earlier in the vector)
            int best_idx = 0;
            uint min_priority = tasks[0].priority;
            
            for (int i = 1; i < tasks.size(); i++) {
                if (tasks[i].priority < min_priority) {
                    min_priority = tasks[i].priority;
                    best_idx = i;
                }
            }
            
            Task& current_task = tasks[best_idx];
            
            // Execute one time unit of the task
            current_task.time--;
            
            // If the task is completed, remove it from the list
            if (current_task.time == 0) {
                tasks.erase(tasks.begin() + best_idx);
            }
            
            // CPU is busy executing this task
            state = busy;
            return make_pair(busy, current_task.task_id);
        }
    };

}

#endif // _SJTU_CPP_FINAL_SRC_HPP_
