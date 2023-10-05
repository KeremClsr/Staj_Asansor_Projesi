#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

#define KAT_SAYISI 62
#define ASANSOR_SAYISI 4
#define MAX_KAPASITE 800

struct Asansor {
    int bulunduguKat;
    int toplamAgirlik;
};

int enYakinAsansor(struct Asansor asansorler[], int hedefKat) {
    int minMesafe = abs(asansorler[0].bulunduguKat - hedefKat);
    int enYakinAsansor = 0;

    for (int i = 1; i < ASANSOR_SAYISI; i++) {
        int mesafe = abs(asansorler[i].bulunduguKat - hedefKat);
        if (mesafe < minMesafe) {
            minMesafe = mesafe;
            enYakinAsansor = i;
        }
    }

    return enYakinAsansor;
}

int isKeyPressed() {
    return _kbhit();
}

char getKeyPress() {
    return _getch();
}

void asansorMenu(int havalandirmaDurumu) {
    printf("\nAsansor menusu:\n");
    printf("a. Acil durum\n");
    printf("h. Havalandirmayi %s\n", havalandirmaDurumu ? "kapatin" : "acin");
    printf("Seciminizi yapin: ");
}

void asansorCalistir(struct Asansor *asansor, int hedefKat, int asansorNumarasi) {
    printf("\n\nAsansor %d, %d. kattan hareket ediyor...\n", asansorNumarasi, asansor->bulunduguKat);

    int havalandirmaDurumu = 0;
    char secim;

    if (asansor->bulunduguKat < hedefKat) {
        while (asansor->bulunduguKat < hedefKat) {
            if (isKeyPressed()) {
                char pressedKey = getKeyPress();
                if (pressedKey == 'm' || pressedKey == 'M') {
                    asansorMenu(havalandirmaDurumu);
                    secim = getKeyPress();
                    if (secim == 'h' || secim == 'H') {
                        havalandirmaDurumu = !havalandirmaDurumu;
                        printf("\nHavalandirma %s.\n", havalandirmaDurumu ? "acildi" : "kapatildi");
                    } else if (secim == 'a' || secim == 'A') {
                        printf("\nAcil durum secildi. Alarm calistirildi. Yetkiliyle konusmak icin basili tutun...\n");
                    } else {
                        printf("\nHatali giris. Lutfen gecerli bir secim yapin. ");
                    }
                }
            }

            asansor->bulunduguKat++;
            Sleep(1000);
        }
    } else {
        while (asansor->bulunduguKat > hedefKat) {
            if (isKeyPressed()) {
                char pressedKey = getKeyPress();
                if (pressedKey == 'm' || pressedKey == 'M') {
                    asansorMenu(havalandirmaDurumu);
                    secim = getKeyPress();
                    if (secim == 'h' || secim == 'H') {
                        havalandirmaDurumu = !havalandirmaDurumu;
                        printf("Havalandirma %s.\n", havalandirmaDurumu ? "acildi" : "kapatildi");
                    } else if (secim == 'a' || secim == 'A') {
                        printf("\n\nAcil durum secildi. Alarm calistirildi. Yetkiliyle konusmak icin basili tutun...");
                    } else {
                        printf("\n\nHatali giris. Lutfen gecerli bir secim yapin. ");
                    }
                }
            }

            asansor->bulunduguKat--;
            Sleep(1000);
        }
    }

    printf("Asansor %d, %d. kata geldi. Kapi acildi. ", asansorNumarasi, asansor->bulunduguKat);
}

int main() {
    struct Asansor asansorler[ASANSOR_SAYISI];
    int hedefKat;

    for (int i = 0; i < ASANSOR_SAYISI; i++) {
        asansorler[i].bulunduguKat = 1;
        asansorler[i].toplamAgirlik = 0;
    }

    while (1) {
        int kisiSayisi;

        do {
            printf("Kacinci kata gidilecek? (1-%d) ", KAT_SAYISI);
            scanf("%d", &hedefKat);

            if (hedefKat < 1 || hedefKat > KAT_SAYISI) {
                printf("\n\nGecersiz bir kat numarasi girdiniz. Lutfen tekrar deneyin. ");
            }
        } while (hedefKat < 1 || hedefKat > KAT_SAYISI);

        int enYakinAsansorIndex = enYakinAsansor(asansorler, hedefKat);
        struct Asansor *enYakinAsansor = &asansorler[enYakinAsansorIndex];

        printf("\nAsansor %d, size yonlendirilecek.", enYakinAsansorIndex + 1);

        do {
            printf("\nToplam agirlik: ");
            scanf("%d", &kisiSayisi);

            if (kisiSayisi <= 0) {
                printf("\n\nGecersiz bir deger girdiniz. Lutfen tekrar deneyin. ");
            }
        } while (kisiSayisi <= 0);

        if (enYakinAsansor->toplamAgirlik + kisiSayisi <= MAX_KAPASITE) {
            enYakinAsansor->toplamAgirlik += kisiSayisi;
            asansorCalistir(enYakinAsansor, hedefKat, enYakinAsansorIndex + 1);
            enYakinAsansor->toplamAgirlik -= kisiSayisi;
        } else {
            printf("\nAsansor 800kg'den fazlasini tasiyamaz!'\n");
        }
    }

    return 0;
}
