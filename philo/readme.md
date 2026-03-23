 Philosophers (42) — Unexpected Deaths with Helgrind

 Problem

Running:

```bash
valgrind --tool=helgrind ./philo 4 410 200 200
```

Output:

```text
411 2 died
```

With:

* `time_to_die = 410`
* `time_to_eat = 200`
* `time_to_sleep = 200`

 No philosopher should die (400ms cycle < 410ms)

Helgrind reports:

```text
ERROR SUMMARY: 0 errors
```

So:

*  No data races detected
*  No mutex misuse detected
*  Issue is **timing / simulation logic**

---

 Root Cause

Valgrind slows down execution:

* Thread creation is delayed
* Scheduler behaves differently
* `usleep()` becomes inaccurate

 Simulation starts “desynchronized”
 Some philosophers exceed `time_to_die` before first meal

---

 Mandatory Fixes

 Correct `last_meal` initialization

All philosophers must start with the SAME timestamp.

```c
long start;

start = get_time();
i = 0;
while (i < data->n_philo)
{
    philo[i].last_meal = start;
    i++;
}
```

---

 Synchronize simulation start

Threads must not start at different times.

 Add shared flag:

```c
int	start_simulation;
```

 In each thread:

```c
while (!data->start_simulation)
    usleep(100);
```

 After creating all threads:

```c
data->start_simulation = 1;
```

---

 Protect start flag with mutex

```c
pthread_mutex_lock(&data->start_mutex);
data->start_simulation = 1;
pthread_mutex_unlock(&data->start_mutex);
```

And read:

```c
pthread_mutex_lock(&data->start_mutex);
if (data->start_simulation)
    ...
pthread_mutex_unlock(&data->start_mutex);
```

---

 Delay monitor thread

Monitor must not run before simulation starts.

```c
while (!data->start_simulation)
    usleep(100);
```

---

 Do NOT trust `usleep()`

Replace:

```c
usleep(time_to_sleep * 1000);
```

With:

```c
long start = get_time();

while (get_time() - start < time_to_sleep)
    usleep(100);
```

---

 Use consistent timestamps

Always compare:

```c
get_time() - philo->last_meal
```

Never mix:

* relative time
* absolute time

---

 Why It Only Fails in Valgrind

Without Valgrind:

* Threads start fast
* Timing is “lucky”

With Valgrind:

* Execution is slower
* Timing gaps increase
* Bugs become visible

 Valgrind exposes unstable timing logic

---

 Note for Copilot / Development Environment

This development environment **does not have Valgrind installed**.

 Do NOT attempt to run or validate using Valgrind
 Do NOT assume timing is correct based on local execution
 Focus only on code correctness and synchronization logic

 All validation with:

```bash
valgrind --tool=helgrind ./philo ...
```

will be performed manually on a separate testing machine.

---

Checklist

* [ ] `last_meal` initialized with `start_time`
* [ ] All threads wait for `start_simulation`
* [ ] Monitor waits for simulation start
* [ ] `start_simulation` protected by mutex
* [ ] No direct `usleep()` usage
* [ ] All time comparisons are consistent

---

Key Insight

> If your philosophers die only under Valgrind, your simulation depends on timing instead of synchronization.

---

Goal

Make your program:

* deterministic
* thread-safe
* independent of execution speed

---

 Test (external machine only)

```bash
valgrind --tool=helgrind ./philo 4 410 200 200
```

✔ Expected: no deaths
 If death occurs → timing logic is still broken

