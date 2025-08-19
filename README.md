# Average BMI Calculation – Performance Comparison in C  

## 📌 Project Description  

This project was developed as part of **ENCS3390: Operating System Concepts**.  
The goal is to calculate the **average Body Mass Index (BMI)** from a dataset and analyze the performance of different parallel computing approaches in **C language**.  

Three approaches are implemented and compared:  

1. **Naive (Serial) Approach**  
   - Reads the dataset sequentially.  
   - Computes BMI values and calculates the average without any parallelism.  
   - Serves as a baseline for performance measurement.  

2. **Multiprocessing Approach**  
   - Uses the `fork()` system call to create multiple child processes.  
   - Each child process computes BMI values for a portion of the dataset.  
   - Results are sent back to the parent process using pipes or shared memory.  
   - The parent process combines the results to calculate the final average BMI.  

3. **Multithreading Approach**  
   - Uses the **POSIX Threads (pthreads)** library.  
   - Creates multiple joinable threads, each handling part of the dataset.  
   - Threads run in parallel and share memory space, which reduces communication overhead compared to processes.  
   - After processing, results are combined to compute the final average BMI.  

### ✨ Key Features  
- Comparison of **serial vs. parallel execution**.  
- Performance measurement with different numbers of processes and threads.  
- Analysis of speedup and efficiency using **Amdahl’s Law**.  
- Works on Linux/Unix systems with at least **4 CPU cores**.  
