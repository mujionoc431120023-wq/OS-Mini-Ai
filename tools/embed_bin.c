#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    if (argc < 4) {
        fprintf(stderr, "Usage: %s <input.bin> <output.c> <symbol>\n", argv[0]);
        return 1;
    }
    const char *infile = argv[1];
    const char *outfile = argv[2];
    const char *sym = argv[3];

    FILE *in = fopen(infile, "rb");
    if (!in) { perror("fopen input"); return 1; }
    fseek(in, 0, SEEK_END);
    long len = ftell(in);
    fseek(in, 0, SEEK_SET);

    unsigned char *buf = malloc(len);
    if (!buf) { fclose(in); return 1; }
    fread(buf, 1, len, in);
    fclose(in);

    FILE *out = fopen(outfile, "w");
    if (!out) { perror("fopen output"); free(buf); return 1; }

    fprintf(out, "unsigned char %s[] = {", sym);
    for (long i = 0; i < len; i++) {
        if (i % 12 == 0) fprintf(out, "\n  ");
        fprintf(out, "0x%02x,", buf[i]);
    }
    fprintf(out, "\n};\nunsigned int %s_len = %ld;\n", sym, len);
    fclose(out);
    free(buf);
    return 0;
}

