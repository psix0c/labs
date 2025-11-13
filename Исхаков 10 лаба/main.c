#include <windows.h>
#include <stdio.h>

#define W_MAX 50
#define H_MAX 50

int m[H_MAX][W_MAX];
int px, py;
int w, h;
int lvl = 1;
HWND g_hwnd = NULL;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

void load(int l) {
    char fname[20];
    sprintf(fname, "level%d.txt", l);

    FILE *f = fopen(fname, "r");
    if (f) {
        fscanf(f, "%d %d", &w, &h);
        fscanf(f, "%d %d", &px, &py);

        for (int i = 0; i < h; ++i) {
            char row[W_MAX + 1];
            fscanf(f, "%s", row);
            for (int j = 0; j < w; ++j) {
                m[i][j] = row[j] - '0';
            }
        }
        fclose(f);
    } else {
        MessageBox(g_hwnd, "Поздравляем! Вы прошли все уровни!", "Победа", MB_OK);
        PostQuitMessage(0);
    }
}

int WINAPI WinMain(HINSTANCE h_inst, HINSTANCE h_prev, LPSTR cmd, int show) {
    const char CNAME[] = "MazeWindowClass";

    WNDCLASS wc = {0};
    wc.lpfnWndProc = WndProc;
    wc.hInstance = h_inst;
    wc.lpszClassName = CNAME;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    RegisterClass(&wc);

    load(lvl);

    g_hwnd = CreateWindowEx(
        0, CNAME, "Maze in C",
        WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX,
        CW_USEDEFAULT, CW_USEDEFAULT, 800, 600,
        NULL, NULL, h_inst, NULL
    );

    if (g_hwnd == NULL) {
        return 0;
    }

    ShowWindow(g_hwnd, show);

    MSG msg = {0};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
    switch (msg) {
        case WM_KEYDOWN: {
            int nx = px;
            int ny = py;

            switch (wp) {
                case VK_LEFT:  nx--; break;
                case VK_RIGHT: nx++; break;
                case VK_UP:    ny--; break;
                case VK_DOWN:  ny++; break;
            }

            if (m[ny][nx] != 1) {
                px = nx;
                py = ny;
            }

            if (m[py][px] == 2) {
                lvl++;
                load(lvl);
            }
            InvalidateRect(hwnd, NULL, TRUE);
            break;
        }

        case WM_PAINT: {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);

            int cell_sz = 30;
            HBRUSH b_wall = CreateSolidBrush(RGB(50, 50, 50));
            HBRUSH b_path = CreateSolidBrush(RGB(255, 255, 255));
            HBRUSH b_exit = CreateSolidBrush(RGB(0, 255, 0));
            HBRUSH b_player = CreateSolidBrush(RGB(255, 0, 0));

            for (int i = 0; i < h; ++i) {
                for (int j = 0; j < w; ++j) {
                    RECT r_cell = {j * cell_sz, i * cell_sz, (j + 1) * cell_sz, (i + 1) * cell_sz};
                    switch (m[i][j]) {
                        case 1: FillRect(hdc, &r_cell, b_wall); break;
                        case 2: FillRect(hdc, &r_cell, b_exit); break;
                        default: FillRect(hdc, &r_cell, b_path); break;
                    }
                }
            }

            RECT r_player = {px * cell_sz, py * cell_sz, (px + 1) * cell_sz, (py + 1) * cell_sz};
            FillRect(hdc, &r_player, b_player);

            DeleteObject(b_wall);
            DeleteObject(b_path);
            DeleteObject(b_exit);
            DeleteObject(b_player);

            EndPaint(hwnd, &ps);
            break;
        }

        case WM_DESTROY:
            PostQuitMessage(0);
            break;

        default:
            return DefWindowProc(hwnd, msg, wp, lp);
    }
    return 0;
}