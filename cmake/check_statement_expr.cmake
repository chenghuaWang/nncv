macro(CHECK_STATEMENT_EXPR)
    check_cxx_source_runs("
    #define max(x, y) ({ x > y ? x : y; })
    int main()
    {
        int a = 10;
        int b = 20;
        int c = max(a, b);
    }
    " HAVE_STATEMENT_EXPR)
if(HAVE_STATEMENT_EXPR)
    message(STATUS "\tstatement expression support - yes")
else()
    message(STATUS "\tstatement expression support - no")
    message(FATAL_ERROR "This lib is depends on Clang/GCC which has statement expression extension !!!")
    EXIT()
endif(HAVE_STATEMENT_EXPR)

endmacro(CHECK_STATEMENT_EXPR)
