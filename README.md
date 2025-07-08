
---

## 📝 Project Description

### Concurrent Singly Linked List – PSW Project

This project is an implementation of a **thread-safe singly linked list in C**, developed as part of the **"System and Concurrent Programming" course (PSW)** during the **3rd semester of Computer Science studies**.

---

### ✅ Key Information

* **University project:** 3rd semester – PSW (Programowanie Systemowe i Współbieżne / System and Concurrent Programming)
* **Programming language:** C with POSIX threads (pthreads)
* **Purpose:** Learn and implement synchronization mechanisms for concurrent data structures

---

### 💡 Project Goals

The main objectives of this project were to:

1. **Design and implement** a singly linked list with full **thread safety** using mutexes and condition variables.
2. Enable **multiple threads to safely add, remove, and retrieve items** concurrently without data races.
3. Practice advanced **POSIX thread synchronization techniques**, including:

   * Mutex locks
   * Condition variables
   * Wait and signal mechanisms

---

### 🔧 Functionalities Implemented

✔️ Create and destroy a concurrent singly linked list
✔️ Add items (`putItem`) and retrieve/remove items (`getItem`, `popItem`) safely
✔️ Remove specific items (`removeItem`)
✔️ Append items from another list (`appendItems`)
✔️ Change the maximum size dynamically (`setMaxSize`)
✔️ Get the current number of items (`getCount`)
✔️ Print the entire list (`showList`)
✔️ **Thread-safe implementation** using `pthread_mutex_t` and `pthread_cond_t`

---

### 🎓 Educational Outcomes

By completing this project, I gained practical experience in:

* Designing **concurrent data structures**
* Implementing **safe producer-consumer mechanisms**
* Using **mutexes and condition variables in C**
* Writing clean, well-documented C code for system-level programming

---

### 👩‍💻 Author

**Jagoda Wesołowska | Jagoda2385**

> Developed as part of the **System and Concurrent Programming (PSW) course** during the 3rd semester of Computer Science studies.

---

