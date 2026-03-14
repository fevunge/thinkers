# Philosophers Dining Problem - Project Overview

## What is This Project?

The **Philosophers Dining Problem** (also known as the Dining Philosophers Problem) is a classic computer science problem that illustrates synchronization issues in concurrent systems. This implementation demonstrates how to manage shared resources, thread coordination, and deadlock prevention in a multi-threaded environment.

## Problem Statement

Imagine a number of philosophers sitting around a circular table, each with a plate of spaghetti. Between each pair of philosophers is a single fork. Each philosopher needs two forks (left and right) to eat.

The challenge is to:
1. Prevent philosophers from starving (dying of hunger)
2. Prevent deadlock (all philosophers waiting for resources)
3. Ensure fair resource distribution

## Project Structure

```
philo/
├── include/
│   └── philo.h              # Main header with structs and function declarations
├── src/
│   ├── main.c               # Entry point, argument parsing
│   ├── dinner.c             # Initialization and lifecycle management
│   ├── waiter.c             # Observer thread (monitors philosopher states)
│   ├── philo.c              # Philosopher logic and thread routines
│   ├── io/
│   │   ├── get_args.c       # Parse command-line arguments
│   │   ├── get_error.c      # Error handling
│   │   └── get_log.c        # Logging with mutex protection
│   └── util/
│       ├── string/
│       │   ├── ft_atoi.c    # Convert string to integer
│       │   ├── ft_strlen.c  # String length
│       │   └── ft_s_is_digit.c # Check if all chars are digits
│       └── time/
│           ├── ft_time_now.c    # Get current time in milliseconds
│           └── ft_usleep.c      # Sleep with busy-wait for accuracy
├── Makefile                 # Build configuration
└── philo               # Compiled executable
```

## How to Use

### Compilation
```bash
make              # Build the project
make clean        # Remove object files
make fclean       # Remove all generated files
make re           # Rebuild from scratch
```

### Running the Program
```bash
./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [times_each_must_eat]
```

**Arguments:**
- `number_of_philosophers`: Number of philosophers (1-200)
- `time_to_die`: Time in milliseconds before a philosopher dies if they don't eat
- `time_to_eat`: Time in milliseconds for eating
- `time_to_sleep`: Time in milliseconds for sleeping
- `times_each_must_eat`: (Optional) Number of times each philosopher must eat before stopping

**Examples:**
```bash
./philo 4 800 200 200        # 4 philosophers, normal scenario
./philo 2 800 200 200 3      # 2 philosophers, each must eat 3 times
./philo 1 500 200 100        # 1 philosopher (will die)
```

## Output Format

Each action is timestamped and thread-safe:
```
timestamp philosopher_id action
```

**Actions:**
- `has taken a fork` - Philosopher picked up a fork
- `is eating` - Philosopher is eating
- `is sleeping` - Philosopher is sleeping
- `is thinking` - Philosopher is thinking
- `died` - Philosopher starved (didn't eat within time_to_die)

**Example Output:**
```
0 1 has taken a fork
0 1 has taken a fork
0 1 is eating
200 1 is sleeping
200 2 is thinking
```

## Core Concepts Implemented

### 1. Mutexes (Mutual Exclusion)
Prevents multiple threads from accessing shared resources simultaneously:
- Fork mutexes: Each fork is protected by a mutex
- Write lock: Protects console output from race conditions
- Meal lock: Protects meal counter and last_meal timestamp

### 2. Thread Management
- **Philosopher threads**: Each philosopher runs independently
- **Waiter thread**: Monitors all philosophers for death or completion
- Proper thread creation and detachment using `pthread_create()` and `pthread_detach()`

### 3. Synchronization
- **Waiter pattern**: An observer thread continuously checks:
  - If any philosopher has starved
  - If all philosophers have eaten their required meals
- Threads are detached to avoid joining (preventing deadlock)

### 4. Timing & Precision
- Uses `gettimeofday()` for precise millisecond timing
- Busy-wait loop in `ft_usleep()` ensures accurate sleep durations
- Handles microsecond resolution for accurate death detection

### 5. Memory Management
- Dynamic allocation for all shared data structures
- Proper cleanup in `finish_dinner()` to prevent memory leaks
- All allocated memory is freed, all mutexes are destroyed

## Key Algorithm: The Waiter Pattern

The program uses a **waiter/observer pattern** instead of trying to prevent deadlock through a specific eating order:

1. **Philosopher Loop** (infinite, until observer stops):
   - Lock left fork
   - Lock right fork
   - Eat (update last_meal time)
   - Unlock forks
   - Sleep
   - Think

2. **Waiter Loop** (continuous monitoring):
   - Check each philosopher's last_meal time
   - If time since last meal > time_to_die → philosopher died
   - If all philosophers have eaten required times → program ends
   - Return and terminate when done

This approach avoids:
- Complex deadlock prevention algorithms
- Philosopher threads needing to check exit conditions
- Race conditions on the "stop" flag

## Memory and Resource Management

### No Memory Leaks
- All malloc'd pointers are freed in `finish_dinner()`
- All pthread_mutex_init() calls are matched with pthread_mutex_destroy()
- No orphaned allocations

### Clean Thread Lifecycle
- Main thread creates waiter and philosopher threads
- Waiter thread runs until a philosopher dies or all have eaten
- Main thread waits for waiter with `pthread_join()`
- Main thread detaches philosopher threads with `pthread_detach()`
- Philosopher threads continue running but are properly cleaned up on process exit

### Thread Safety
All shared data is protected by mutexes:
- Fork access: fork mutexes
- Output: write lock
- Meal counters: meal lock

## Critical Sections

1. **Fork acquisition** - Each fork is locked separately to prevent concurrent access
2. **Meal update** - Atomic update to eaten counter and last_meal timestamp
3. **Console output** - All printf calls are protected by write_lock
4. **Death detection** - Read last_meal under meal_lock protection

## Testing

The project includes a test script (`test.sh`) that verifies:
- ✓ Normal completion with meal limits
- ✓ Death detection when philosopher starves
- ✓ Error handling for invalid arguments
- ✓ Single philosopher scenario

## Compilation Flags

```bash
CFLAGS = -Wall -Werror -Wextra
```
- `-Wall`: Enable all warnings
- `-Werror`: Treat warnings as errors
- `-Wextra`: Extra warning checks

## Performance Characteristics

- **Time Complexity**: O(n) for waiter monitoring (n = number of philosophers)
- **Space Complexity**: O(n) for philosopher and fork structures
- **Thread Count**: n philosophers + 1 waiter = (n+1) total threads
- **Mutex Count**: n forks + 2 global (write_lock, meal_lock) = (n+2) total

## Known Behaviors

1. **Philosopher with two forks**: Takes both forks sequentially, not atomically
2. **Timing precision**: Depends on system scheduler (typically within 10ms)
3. **Death message timing**: Printed within 10ms of actual starvation
4. **Resource exhaustion**: Program fails gracefully if mutex/thread creation fails
