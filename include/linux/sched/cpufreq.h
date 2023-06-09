/* SPDX-License-Identifier: GPL-2.0 */
#ifndef _LINUX_SCHED_CPUFREQ_H
#define _LINUX_SCHED_CPUFREQ_H

#include <linux/types.h>

/*
 * Interface between cpufreq drivers and the scheduler:
 */

#define SCHED_CPUFREQ_IOWAIT	(1U << 0)

#ifdef CONFIG_CPU_FREQ
struct cpufreq_policy;

struct update_util_data {
       void (*func)(struct update_util_data *data, u64 time, unsigned int flags);
};

void cpufreq_add_update_util_hook(int cpu, struct update_util_data *data,
                       void (*func)(struct update_util_data *data, u64 time,
				    unsigned int flags));
void cpufreq_remove_update_util_hook(int cpu);
bool cpufreq_this_cpu_can_update(struct cpufreq_policy *policy);

static bool last_exp_util;
static inline unsigned long map_util_freq(unsigned long util,
					unsigned long freq, unsigned long cap, bool exp_util)
{
       last_exp_util = exp_util;
       if(exp_util)
              return (freq + (freq >> 2)) * int_sqrt(util * 100 / cap) / 10;
       else
              return (freq + (freq >> 2)) * util / cap;
}
#endif /* CONFIG_CPU_FREQ */

#endif /* _LINUX_SCHED_CPUFREQ_H */
