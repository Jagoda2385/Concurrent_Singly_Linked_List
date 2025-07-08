📝 Project Description
Concurrent Singly Linked List – PSW Project
This project is an implementation of a thread-safe singly linked list in C, developed as part of the "System and Concurrent Programming" course (PSW) during the 3rd semester of studies.

✅ Key Information
University project: 3rd semester, PSW (Programowanie Systemowe i Współbieżne – System and Concurrent Programming)

Programming language: C with POSIX threads (pthreads)

Purpose: Learn and implement synchronization mechanisms for concurrent data structures

💡 Project Goal
The goal of this project was to:

Design and implement a singly linked list with full thread safety using mutexes and condition variables.

Enable multiple threads to safely add, remove, and retrieve items from the list concurrently without data races.

Practice advanced POSIX thread synchronization techniques, including:

Mutex locks

Condition variables

Wait and signal mechanisms

🔧 Functionalities Implemented
✔️ Create and destroy a concurrent singly linked list
✔️ Add items (putItem) and retrieve/remove items (getItem, popItem) safely
✔️ Remove a specific item (removeItem)
✔️ Append items from another list (appendItems)
✔️ Change the maximum size dynamically (setMaxSize)
✔️ Get the current count of items (getCount)
✔️ Print the entire list (showList)
✔️ Thread-safe implementation using pthread_mutex_t and pthread_cond_t

🎓 Educational Outcomes
By completing this project, I gained practical experience in:

Designing concurrent data structures

Implementing safe producer-consumer mechanisms

Using mutexes and condition variables in C

Writing clean, well-documented C code for system-level programming

👩‍💻 Author
Jagoda Wesołowska | Jagoda2385

Developed as part of the System and Concurrent Programming course (PSW) during my Computer Science studies, 3rd semester.

