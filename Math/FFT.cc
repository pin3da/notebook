typedef long double T;

const T pi = acos(-1);

struct cpx {
    T real, image;
    cpx(T _real, T _image) {
        real = _real;
        image = _image;
    }
    cpx() {}
};

cpx operator + (const cpx &c1, const cpx &c2) {
    return cpx(c1.real + c2.real, c1.image + c2.image);
}
cpx operator - (const cpx &c1, const cpx &c2) {
    return cpx(c1.real - c2.real, c1.image - c2.image);
}
cpx operator * (const cpx &c1, const cpx &c2) {
    return cpx(c1.real * c2.real - c1.image * c2.image , c1.real *c2.image + c1.image * c2.real);
}

int rev(int id, int len) {
    int ret = 0;
    for (int i = 0; (1 << i) < len; i++) {
        ret <<= 1;
        if (id & (1 << i)) ret |= 1;
    }
    return ret;
}

void fft(cpx *a, int len, int dir) {
    for (int i = 0; i < len; i++) {
        A[rev(i, len)] = a[i];
    }

    for (int s = 1; (1 << s) <= len; s++) {
        int m = (1 << s);

        cpx wm = cpx(cos(dir * 2 * pi / m), sin(dir * 2 * pi / m ));
        for (int k = 0; k < len; k += m) {
            cpx w = cpx(1, 0);
            for (int j = 0; j < (m >> 1); j++) {
                cpx t = w * A[k + j + (m >> 1)];
                cpx u = A[k + j];
                A[k + j] = u + t;
                A[k + j + (m >> 1)] = u - t;
                w = w * wm;
            }
        }
    }
    if (dir == -1) for (int i = 0; i < len; i++) A[i].real /= len, A[i].image /= len;
    for (int i = 0; i < len; i++) a[i] = A[i];
}
