__kernel void mult(__global const int *x,
                   __global const int *y,
                   __global int *z,
                   const int N,
                   const int M,
                   const int L)
{
    int i = get_global_id(0); // tread #1
    int j = get_global_id(1); // tread #2
    
    int buf = 0;
    for (int k = 0; k < M; k++)
    {
        buf += x[i * M + k] * y[k * L + j];
    }
    z[i * L + j] = buf;
}
