# Philosophers
# Threads
#threads
## Definition
Threads in C are a way to achieve concurrent execution of code, allowing a program to perform multiple operations simultaneously. This is particularly useful for tasks that can be executed independently, such as handling multiple client connections in a server or performing background computations while maintaining responsiveness in the main application. **created by `edsger Dijkstra`**
## Parallelism vs concurrency
Concurrent and parallel are effectively the same principle as you correctly surmise, both are related to tasks being executed simultaneously although I would say that parallel tasks should be truly multitasking, executed "at the same time" whereas concurrent could mean that the tasks are sharing the execution thread while still appearing to be executing in parallel.
## Benefits
### Responsiveness
Multi-threading  an interactive application may allow a program to continue running even if part of it is blocked or is performing a lengthy operation. 
### Resource sharing
The benefit of sharing code and data is that it allows an application to have several different threads of activity  within the same address space. 
### Economy
Allocating memory and resources for process creation costly. Because threads share resources of the process to which they belong, it is more economical to create and context-switch threads.

# Multi-threading Models
## Types of Threads 
**`User threads`** : Supported above the kernel and are managed without kernel support.
**`Kernel threads`** : Supported and managed directly by the operating system.
`There are a relationships between user threads and kernel threads`.
## Relationships of user and kernel threads
### Many-to-One Model
**`Postive side`** :
- Maps many user-level threads in one kernel thread.
- thread management is in user-level, so it efficient.
**`Negative side`** : 
- the entire process block if a thread blocked.
- you can't run multiple threads in parallel.
### One-to-One Model
**`Postive side`** : 
- avoiding block of the process if a any thread blocked.
- allows multiple threads to run parallel on multiprocessors.
**`Negative side`** :
- each user thread requires creating a kernel thread, but there's a limits of  kernel threads that means you limit access of creation user threads.
### Many-to-One Model
**`Positive side`** : 
- Multiplexes many user Threads to smaller or equal number of kernel threads.
- You can create as many threads as necessary, and it can run parallel on a  multiprocessor.
- When a threads performs a blocking system call, the kernel can schedule another thread of execution.
**`Negative side`** : 
- NONE !!
# Mutual exclusion (Mutex)
### Definition
A mutex, short for mutual exclusion, is a synchronization primitive used in concurrent programming to protect shared data from being accessed by multiple threads simultaneously. It ensures that only one thread can hold the mutex at a time, preventing race conditions and data corruption.
### pthread_mutex_init
#### Prototype
```c
int pthread_mutex_init(pthread_mutex_t *restrict mutex,
      const pthread_mutexattr_t *restrict attr);
```
### Definition
The pthread_mutex_init function initializes the mutex referenced by mutex with the attributes specified by attr. If attr is NULL, the default mutex attributes are used.
The mutex is used to protect shared resources from being accessed simultaneously by multiple threads, ensuring mutual exclusion.
### ARGs 
`**thread**`:  A pointer to the mutex to be initialized.

`**attr**`:  A pointer to a mutex attributes object, or NULL for default attributes.
### Return 
The function itself returns 0 if the creation was successful, or en error code if not.

# Thread function
## pthread_create
### Prototype
```c
int pthread_create(pthread_t *restrict thread,
                    const pthread_attr_t *restrict attr,
                    void *(*start_routine)(void *),
                    void *restrict arg);
```
### Definition
pthread_create is a function in the POSIX Threads (pthreads) library, used to create a new thread in a C/C++ program. It is part of the POSIX standard (Portable Operating System Interface), which defines a set of consistent and standardized APIs for thread management across different Unix-like operating systems.
### ARGs 
`**thread**`: a pointer towards a pthread_t type variable, to store the ID of the thread we will be creating.
`**attr**`: an argument that allows us to change the default attributes of the new thread. This is beyond the scope of this article, and in general, passing NULL here suffices.
`**start_routine:**` the function where the thread will start its execution. This function will have as its prototype: void \*function_name(void \*arg);. When the thread reaches the end of this function, it will be done with its tasks.
`**arg**`: a pointer towards an argument to pass to the thread’s start_routine function. If we’d like to pass several parameters to this function, we will need to give it a pointer to a data structure.
### Return 
The function itself returns 0 if the creation was successful, or en error code if not.

## pthread_join
### Prototype
```c
 int pthread_join(pthread_t thread, void **retval);
```
### Definition 
pthread_join is a function in the POSIX Threads (pthreads) library that allows one thread to wait for the termination of another thread. When a thread calls pthread_join on another thread, it blocks until the specified thread terminates. This is useful for ensuring that a thread has completed its execution before continuing with the main program or other threads.
### ARGs
`**thread**`: the ID of the thread that this thread should wait for. The specified thread must be joinable (meaning not detached – see below).
`**retval**`: a pointer towards a variable that can contain the return value of the thread’s routine function (the start_routine function we supplied at its creation). Here, we will not need this value: a simple NULL will suffice.
### Return 
The function itself returns 0 if the creation was successful, or en error code if not.
## pthread_detach
### Prototype
```c
int pthread_detach(pthread_t thread);
```
### Definition
pthread_detach is a function in the POSIX Threads (pthreads) library that is used to mark a thread as detached. When a thread is detached, its resources are automatically released back to the system when it terminates, without the need for another thread to call pthread_join on it. This is useful for threads that run independently and do not need to return a value or be synchronized with other threads.
### ARGs
`**thread**`: the ID of the thread that this thread should wait for. The specified thread must be joinable (meaning not detached – see below).
### Return 
The function itself returns 0 if the creation was successful, or en error code if not.

# bonus
## Semaphore
### Definition
Semaphores are just normal variables used to coordinate the activities of multiple processes in a computer system. They are used to enforce mutual exclusion, avoid race conditions, and implement synchronization between processes.

### Named vs unnamed semaphore
POSIX semaphores can be unnamed or named. Unnamed semaphores are allocated in process memory and initialized. Unnamed semaphores might be usable by more than one process, depending on how the semaphore is allocated and initialized. Unnamed semaphores are either private, inherited through fork(), or are protected by access protections of the regular file in which they are allocated and mapped.
Named semaphores are like process-shared semaphores, except that named semaphores are referenced with a pathname rather than a pshared value. Named semaphores are sharable by several processes. Named semaphores have an owner user-id, group-id, and a protection mode.

![Screenshot from 2024-09-04 11-40-09](https://github.com/user-attachments/assets/4dfff0d8-0e10-4ff4-a83f-7896f5f69d10)


