#include <systemc.h>

struct test_module : sc_module {
    SC_HAS_PROCESS(test_module);

    test_module(::sc_core::sc_module_name) {
        SC_THREAD(test_thread);
    }

    sc_signal<std::string>  message{ "message" };

    void test_thread() {
        message.write("Hello world!");
        wait(1, SC_NS);
        cout << message.read() << endl;
        sc_stop();
    }
};

int sc_main(int argc, char** argv)
{
    test_module tmod{ "tmod" };
    sc_start(200, SC_MS);
    return 0;
}