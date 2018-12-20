#include "combined.h"

void comb(double in[FM_HEIGHT][FM_WIDTH], double kern[KERN_HEIGHT][KERN_WIDTH], double out[FM_HEIGHT][FM_WIDTH]) {

    // find center position of kernel (half of kernel size)
    int kCenterX = KERN_WIDTH / 2;
    int kCenterY = KERN_HEIGHT / 2;

    int i,j,m,n, xpos, ypos, max_val;

    for (i = 0; i < FM_HEIGHT; ++i)              // rows
    {
        for (j = 0; j < FM_WIDTH; ++j)          // columns
        {
            for (m = 0; m < KERN_HEIGHT; ++m)     // kernel rows
            {
                int mm = KERN_HEIGHT - 1 - m;      // row index

                for (n = 0; n < KERN_WIDTH; ++n) // kernel columns
                {
                    int nn = KERN_WIDTH - 1 - n;  // column index

                    // index of input signal, used for checking boundary
                    int ii = i + (m - kCenterY);
                    int jj = j + (n - kCenterX);

                    // ignore input samples which are out of bound
                    if (ii >= 0 && ii < FM_HEIGHT && jj >= 0 && jj < FM_WIDTH)
                        out[i][j] += in[ii][jj] * kern[mm][nn];
                }
            }
        }
    }

    for (i = 0; i < FM_HEIGHT; i++) {
        for (j = 0; j < FM_WIDTH; j++) {
            out[i][j] = MAX(in[i][j],0);
        }
    }

    for (ypos = 0; ypos < FM_HEIGHT; ypos+=2) {
        for (xpos = 0; xpos < FM_WIDTH; xpos+=2) {
            max_val = 0;
            for (i = ypos; i < ypos+2; i++) {
                for (j = xpos; j < xpos+2; j++) {
                    max_val = MAX(max_val,in[i][j]);
                }
            }
            out[ypos/2][xpos/2] = max_val;
        }
    }
}
