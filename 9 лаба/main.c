#include <windows.h>
#include <stdio.h>

#define R_MAX 10
#define C_MAX 10
int a[R_MAX][C_MAX];
int r = 0;
int c = 0;

#define N_COLORS 6
COLORREF colors[N_COLORS] = {
    RGB(20, 20, 20),
    RGB(255, 87, 34),
    RGB(33, 150, 243),
    RGB(76, 175, 80),
    RGB(255, 235, 59),
    RGB(156, 39, 176)
};
HBRUSH brushes[N_COLORS];

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
    switch (msg) {
        case WM_CREATE: {
            FILE* f;
            if (fopen_s(&f, "data.txt", "r") != 0 || f == NULL) {
                MessageBox(hwnd, "Не удалось открыть файл data.txt", "Ошибка", MB_OK | MB_ICONERROR);
                return -1;
            }

            fscanf_s(f, "%d %d", &r, &c);

            if (r > R_MAX) r = R_MAX;
            if (c > C_MAX) c = C_MAX;

            for (int i = 0; i < r; i++) {
                for (int j = 0; j < c; j++) {
                    fscanf_s(f, "%d", &a[i][j]);
                }
            }
            fclose(f);

            if (r > 0 && c > 0) {
                int min_v = a[0][0];
                int min_r = 0, min_c = 0;

                for (int i = 0; i < r; i++) {
                    for (int j = 0; j < c; j++) {
                        if (a[i][j] < min_v) {
                            min_v = a[i][j];
                            min_r = i;
                            min_c = j;
                        }
                    }
                }

                for (int j = 0; j < c; j++) a[min_r][j] = 0;
                for (int i = 0; i < r; i++) a[i][min_c] = 0;
            }

            for (int i = 0; i < N_COLORS; i++) {
                brushes[i] = CreateSolidBrush(colors[i]);
            }
            break;
        }

        case WM_PAINT: {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);

            if (r > 0 && c > 0) {
                RECT client_r;
                GetClientRect(hwnd, &client_r);

                int rect_w = client_r.right / c;
                int rect_h = client_r.bottom / r;

                for (int i = 0; i < r; i++) {
                    for (int j = 0; j < c; j++) {
                        int v = a[i][j];
                        HBRUSH brush = brushes[v % N_COLORS];
                        RECT rect = { j * rect_w, i * rect_h, (j + 1) * rect_w, (i + 1) * rect_h };
                        FillRect(hdc, &rect, brush);
                    }
                }
            }
            EndPaint(hwnd, &ps);
            break;
        }

        case WM_DESTROY: {
            for (int i = 0; i < N_COLORS; i++) {
                DeleteObject(brushes[i]);
            }
            PostQuitMessage(0);
            break;
        }

        default:
            return DefWindowProc(hwnd, msg, wp, lp);
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE h_inst, HINSTANCE h_prev, LPSTR cmd, int show) {
    const char CNAME[] = "StaticArrayViz";
    WNDCLASS wc = { 0 };
    wc.lpfnWndProc = WndProc;
    wc.hInstance = h_inst;
    wc.lpszClassName = CNAME;
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(
        0, CNAME, "Визуализация (Статический массив)", WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 600, 500,
        NULL, NULL, h_inst, NULL
    );

    if (hwnd == NULL) return 0;

    ShowWindow(hwnd, show);
    UpdateWindow(hwnd);

    MSG msg = { 0 };
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}