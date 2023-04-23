/* SPDX-License-Identifier: GPL-2.0 */

#define IOWAIT_BOOST_MIN	(SCHED_CAPACITY_SCALE / 8)

#ifdef CONFIG_OPLUS_MULTI_LV_TL
enum ua_util_type {
	UA_UTIL_SYS,
	UA_UTIL_FBG,
	UA_UTIL_SIZE,
};

struct multi_target_loads {
	unsigned int	*target_loads;
	unsigned int	*util_loads;
	int		ntarget_loads;
};
#endif

struct sugov_tunables {
	struct gov_attr_set	attr_set;
	unsigned int		rate_limit_us;
	bool 				exp_util;
	bool				cobuck_enable;
#ifdef CONFIG_OPLUS_UAG_USE_TL
	spinlock_t			target_loads_lock;
	unsigned int			*target_loads;
	unsigned int			*util_loads;
	int				ntarget_loads;
#endif

#ifdef CONFIG_OPLUS_UAG_AMU_AWARE
	bool				stall_aware;
	u64				stall_reduce_pct;
	int				report_policy;
#endif

#ifdef CONFIG_OPLUS_MULTI_LV_TL
	bool				multi_tl_enable;
	struct multi_target_loads	multi_tl[UA_UTIL_SIZE];
#endif
};

struct sugov_policy {
	struct cpufreq_policy	*policy;

	struct sugov_tunables	*tunables;
	struct list_head	tunables_hook;

	raw_spinlock_t		update_lock;	/* For shared policies */
	u64			last_freq_update_time;
	s64			freq_update_delay_ns;
	unsigned int		next_freq;
	unsigned int		cached_raw_freq;

	/* The next fields are only needed if fast switch cannot be used: */
	struct			irq_work irq_work;
	struct			kthread_work work;
	struct			mutex work_lock;
	struct			kthread_worker worker;
	struct task_struct	*thread;
	bool			work_in_progress;

	bool			limits_changed;
	bool			need_freq_update;
	bool			cobuck_boosted;

	unsigned int		len;
#ifdef CONFIG_OPLUS_MULTI_LV_TL
	unsigned long		multi_util[UA_UTIL_SIZE];
	unsigned int		multi_util_type;
	unsigned int		fbg_gt_sys_cnt;
	unsigned int		total_cnt;
#endif
};

#define MAX_CLUSTERS 3
static int init_flag[MAX_CLUSTERS];

#ifdef CONFIG_UAG_NONLINEAR_FREQ_CTL
int init_opp_cap_info(struct proc_dir_entry *dir);
void clear_opp_cap_info(void);

unsigned int pd_get_nr_caps(int cluster_id);
unsigned long pd_get_opp_capacity(int cpu, int opp);
unsigned int pd_get_cpu_freq(int cpu, int idx);
void nlopp_map_util_freq(void *data, unsigned long util, unsigned long freq,
				  struct cpumask *cpumask, unsigned long *next_freq);
#endif /* CONFIG_UAG_NONLINEAR_FREQ_CTL */

#ifdef CONFIG_OPLUS_UAG_USE_TL
unsigned int choose_util(struct sugov_policy *sg_policy, unsigned int util);
bool get_capacity_margin_dvfs_changed_uag(void);
#endif /* CONFIG_OPLUS_UAG_USE_TL */
