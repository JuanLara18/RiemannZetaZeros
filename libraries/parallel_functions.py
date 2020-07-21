from multiprocessing import Process
import os
import numpy as np

def call_findroots(start, end, find, prec, error, n, maxRun=100):
    """
    This function calls the function find_root for each nuclei, and writes the
    output in a .txt file.
    Input:
        - start: double.
        - end: double.
        - find: bool.
        - prec: double.
        - error: double.
        - n: integer.
        - maxRun: integer (default=100). Longest interval to be executed per
            run.
    Output:
        - void. (it writes in a .txt file)
    """
    
    intervals = [start, end]
    if (end-start)>maxRun:
        count = start
        while count < end:
            count += maxRun
            intervals.insert(-1, count)
    for ii in range(1, len(intervals)):
        order = "g++ -I libraries/boost_1_73_0/ libraries/find_roots.cpp -o a%i.out && "%n
        order += "./a%i.out %f %f %i %f %f"%(n, intervals[ii-1], intervals[ii], find, prec, error)
        order += " >> tmp/%i.txt"%n
        os.system(order)
        os.system("rm a%i.out"%n)

def finding_roots(start, end, find = 0, prec =0.01, error = 0.001, nuclei=1):
    """
        This function parallelizes the function find_roots from main_libraries.h,
        and for that receives the argument nuclei, an integer that counts the
        number of nuclei that are going to be used.

        Input:
            - start: double.
            - end: double.
            - find: bool.
            - prec: double.
            - error: double.
            - nuclei: integer.
        Output:
            - result: integer or array, depending of the variable find.
    """
    try:
        os.system("rm -rf tmp/")
    except:
        pass
    os.mkdir("tmp")
    step = (end-start)/nuclei
    P = [Process(target = call_findroots, args = (start+ii*step, start+(ii+1)*step,\
    find, prec, error, ii+1)) for ii in range(nuclei)]
    try:
        for ii in P:
            ii.start()
        for ii in P:
            ii.join()
    except KeyboardInterrupt:
        for ii in P:
            ii.terminate()

    files = sorted([f for f in os.listdir("tmp/") if os.path.isfile(os.path.join("tmp/", f))])
    result = []
    number = 0

    for ii, f in enumerate(files):
        data = np.loadtxt("tmp/"+f)
        if find == 1:
            number += data[0]
            result.append(data[1:])
        else:
            number += sum(data)
    os.system("rm -rf tmp/")
    if find == 1:
        return np.hstack(tuple(result))
    return number

def call_nmroots(n, m, prec = 0.01, error = 0.001):
    """
        This function calls the function nm_roots, and writes the output in a
        .txt file.
        Input:
            - n: int.
            - m: int.
            - prec: float.
            - error: float.
        Output:
            - void. (it writes in a .txt file)
    """
    try:
        os.system("rm -rf tmp/")
    except:
        pass
    os.mkdir("tmp")
    order = "g++ -I libraries/boost_1_73_0/ libraries/nm_roots.cpp -o a.out && "
    order += "./a.out %i %i %f %f"%(n,m, prec, error)
    order += " > tmp/res.txt"
    os.system(order)
    data = np.loadtxt("tmp/res.txt")
    os.system("rm a.out")
    os.system("rm -rf tmp/")

    return data
