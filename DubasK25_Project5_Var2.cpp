#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <future>
#include <syncstream>

using namespace std;

void solve(const string& name, int duration) {
    osyncstream(cout) << name << " started...\n";
    this_thread::sleep_for(chrono::seconds(duration));
    osyncstream(cout) << name << " finished.\n";
}

void work() {
    auto start = chrono::high_resolution_clock::now();

    auto a2_handle = async(launch::async, solve, "A2", 7);
    auto a3_handle = async(launch::async, solve, "A3", 7);

    solve("A1", 1);
    solve("A4", 1);

    a2_handle.get();
    solve("B", 1);

    solve("D", 1);

    a3_handle.get();
    solve("C", 1);

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = end - start;

    osyncstream(cout) << "Total time: " << elapsed.count() << "s\n";
    osyncstream(cout) << "Work is done!\n";
}

int main() {
    work();
    return 0;
}