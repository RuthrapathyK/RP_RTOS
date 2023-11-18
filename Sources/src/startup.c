int main(void);

unsigned int * vector_table[2] __attribute__ ((section (".isr_vector"))) = {
    (unsigned int *)0x20000400,
    (unsigned int *)&main
};
