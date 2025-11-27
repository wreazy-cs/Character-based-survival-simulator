/*
 * ======================================================================================
 * ÖĞRENCİ ADI SOYADI : SAMET MUHAMMED ALİ ŞAFAK
 * ÖĞRENCİ NUMARASI   : 1250505013
 * OKUL / BÖLÜM       : KIRKLARELİ ÜNİVERSİTESİ / YAZILIM MÜHENDİSLİĞİ
 * DERS               : ALGORİTMA VE PROGRAMLAMA 1
 *
 * PROJE KONUSU       : KARAKTER TABANLI HAYATTA KALMA SİMÜLATÖRÜ
 * ======================================================================================
 * PROJE AÇIKLAMASI:
 * Bu program, C dilinin temel yapı taşlarını (Döngüler, Karar Yapıları, Değişkenler)
 * kullanarak oluşturulmuş interaktif bir oyundur.
 *
 * KULLANILAN YAPILAR VE NEDENLERİ:
 * 1. DO-WHILE: Oyun menüsünün, kullanıcı çıkış diyene kadar en az bir kez çalışması için.
 * 2. FOR DÖNGÜSÜ: 'Tehlike' modunda saldırıların dalga dalga gelmesi için.
 * 3. SWITCH-CASE: Kullanıcının girdiği komutları (A, S, R vb.) yönetmek için.
 * 4. FGETS & WHILE: Kullanıcıdan veri alırken 'boşluk' ve 'tab' hatasını önlemek için.
 * 5. RAND & SRAND: Oyunun her açılışta farklı ihtimaller üretmesi için.
 * ======================================================================================
 */

#include <stdio.h>  // printf, fgets gibi giriş/çıkış fonksiyonları için gerekli kütüphane.
#include <stdlib.h> // rand() ve srand() fonksiyonlarını kullanmak için gerekli.
#include <time.h>   // time() fonksiyonu ile rastgele sayı üretimini zamana bağlamak için.

int main() {
    /* * RASTGELE SAYI ÜRETECİNİ BAŞLATMA (SEEDING)
     * Bilgisayarlar aptaldır, rastgele sayı üretemezler. Eğer srand kullanmazsam
     * programı her açtığımda aynı olaylar yaşanır. time(NULL) diyerek şu anki saati
     * tohum olarak veriyorum ki her oyun benzersiz olsun.
     */
    srand(time(NULL));

    // --- OYUNCU DEĞİŞKENLERİ ---
    int saglik = 100; // Can puanım. 0 olursa ölürüm.
    int enerji = 100; // Hareket gücüm. 0 olursa bayılırım.
    int yemek = 0;    // Topladığım yemek sayısı.
    int siginak = 0;  // Barınma durumu. 0: Yok, 1: Mağara, 2: Baraka.
    
    char komut;       // Kullanıcının klavyeden girdiği harfi tutacak değişken.
    int hasar = 0;    // Olaylardan aldığım hasarı geçici olarak tutan değişken.

    // --- GİRİŞ EKRANI TASARIMI ---
    // Kullanıcı oyuna başlarken kuralları bilsin diye printf ile bilgi veriyorum.
    printf("\n");
    printf("      /\\                                                       /\\\n");
    printf("     /  \\      KARAKTER TABANLI HAYATTA KALMA SİMÜLATÖRÜ      /  \\\n");
    printf("    /    \\     -----------------------------------------     /    \\\n");
    printf("   /      \\                                                 /      \\\n");
    printf("  /  /\\    \\        [ YAZILIM MÜHENDİSLİĞİ BÖLÜMÜ ]        /    /\\  \\\n");
    printf("======================================================================\n");
    printf("||                                                                  ||\n");
    printf("||   [ KOMUTLAR ]                                                   ||\n");
    printf("||   [A] AVLAN    : Tavşan yakala (+Yemek, -15 Enerji)              ||\n");
    printf("||   [S] SIĞINAK  : Mağara veya Baraka ara (-30 Enerji)             ||\n");
    printf("||   [R] DİNLEN   : Yemek yiyerek Canını ve Enerjini toparla        ||\n");
    printf("||   [F] TEHLİKE  : Deprem ve Kurt sürüsüne karşı hayatta kal!      ||\n");
    printf("||   [P] GİZEM    : Şifreli sandıkları çöz, ödül kazan              ||\n");
    printf("||   [E] ENVANTER : Detaylı durumunu gör                            ||\n");
    printf("||   [X] ÇIKIŞ    : Oyunu kapat                                     ||\n");
    printf("||                                                                  ||\n");
    printf("||   [ KURALLAR & UYARILAR ]                                        ||\n");
    printf("||   1. Eylemler için maliyetten FAZLA enerjin olmalıdır!           ||\n");
    printf("||      (Örn: Avlanmak için 15 değil, en az 16 enerji gerekir)      ||\n");
    printf("||   2. Enerji veya Sağlık 0 olursa oyun biter (Ölürsün).           ||\n");
    printf("||   3. Sığınaklar (Mağara/Baraka) seni Kurtlardan %%100 korur.      ||\n");
    printf("||   4. DİKKAT: Deprem olursa sığınağın tavanı çöküp hasar verebilir||\n");
    printf("||   5. Şifreyi yanlış girersen Enerji kaybedersin.                 ||\n");
    printf("======================================================================\n");
    printf("\n>> Simülasyon yükleniyor... Başlamak için hazır olun!\n");

    /* * ANA OYUN DÖNGÜSÜ (DO-WHILE)
     * Oyunun sürekli devam etmesi gerekiyor. "do-while" kullandım çünkü
     * oyun açıldığında menünün en az bir kere görünmesini istiyorum.
     * Döngü, kullanıcı 'X' diyene kadar veya ölene kadar devam edecek.
     */
    do {
        // Her tur başında oyuncuya durumunu gösteriyorum.
        printf("\n------------------------------------------------------------\n");
        printf("DURUM RAPORU -> [ SAĞLIK: %d %% | ENERJİ: %d %% ]\n", saglik, enerji);
        printf("KOMUTLAR     -> [A] [S] [E] [R] [F] [P] [X]\n");
        printf("------------------------------------------------------------\n");
        printf("Ne yapacaksın?: ");

        /* * GÜVENLİ VERİ GİRİŞİ (INPUT SANITIZATION)
         * scanf("%c") kullanmadım çünkü scanf, Enter tuşunu bellekte bırakıyor ve
         * bir sonraki turda oyun "Geçersiz Komut" hatası veriyor.
         * Bunun yerine fgets kullanarak satırı komple okuyorum.
         */
        char satir[100]; // Kullanıcının girdiği yazıyı tutacak dizi.
        
        // Eğer fgets NULL dönerse (Ctrl+D yapılırsa) program çökmesin diye break koydum.
        if (fgets(satir, 100, stdin) == NULL) break;

        /*
         * BOŞLUK VE TAB TEMİZLEME (WHILE DÖNGÜSÜ)
         * Kullanıcı yanlışlıkla boşluk tuşuna basıp sonra 'A' yazarsa oyun hata vermesin.
         * Bu döngü, baştaki tüm boşlukları atlar ve gerçek harfi bulur.
         */
        int k = 0;
        while (satir[k] == ' ' || satir[k] == '\t') {
            k++; // Boşluk gördükçe bir sonraki karaktere geç
        }
        
        // Eğer kullanıcı sadece Enter'a bastıysa (\n) döngüyü pas geçip tekrar sorsun.
        if (satir[k] == '\n' || satir[k] == '\0') {
            continue; 
        }

        // Temizlenen satırdaki ilk geçerli karakteri komut olarak alıyorum.
        komut = satir[k];

        // KÜÇÜK HARFİ BÜYÜĞE ÇEVİRME
        // Kullanıcı 'a' girerse, ASCII tablosunda 32 çıkararak onu 'A' yapıyorum.
        // Böylece switch-case içinde hem 'a' hem 'A' yazmama gerek kalmıyor.
        if (komut >= 'a' && komut <= 'z') {
            komut = komut - 32;
        }

        /*
         * KARAR MEKANİZMASI (SWITCH-CASE)
         * Kullanıcının girdiği komuta göre ilgili oyun kodunu çalıştırır.
         */
        switch (komut) {
            
            // --- [A] AVLANMA DURUMU ---
            case 'A':
                // KURAL: 15 Enerjim varken 15 harcarsam 0 kalır ve ölürüm.
                // Bu yüzden 15'ten BÜYÜK olması şartını koydum (> 15).
                if (enerji > 15) {
                    enerji -= 15; // Enerji harcanıyor
                    
                    int sans = rand() % 100; // 0-99 arası rastgele sayı
                    if (sans > 40) { // %60 şansla (40'tan büyükse)
                        yemek++;
                        printf("\n>> [BAŞARILI] Bir tavşan yakaladın! (+1 Yemek)\n");
                    } else {
                        // Başarısız olunca 1 ile 5 arası rastgele hasar alıyoruz
                        int avHasari = (rand() % 5) + 1;
                        saglik -= avHasari;
                        printf("\n>> [BAŞARISIZ] Ormanda düştün ve yaralandın. (-%d Sağlık)\n", avHasari);
                    }
                } else {
                    // Kullanıcıyı uyarıyorum
                    printf("\n>> [UYARI] Avlanmak için 15'ten FAZLA enerji lazım! (Şu an: %d) -> [R] Dinlen \n", enerji);
                }
                break;

            // --- [S] SIĞINAK ARAMA DURUMU ---
            case 'S':
                // Zaten sığınağım varsa tekrar aratmıyorum (Enerji israfı olmasın)
                if (siginak == 0) {
                    if (enerji > 30) { // En az 31 enerji lazım
                        enerji -= 30; 
                        printf("\n>> Güvenli bir yer arıyorsun...\n");
                        
                        int sans = rand() % 100;
                        if (sans < 30) { // %30 İhtimalle bulur
                            
                            // Bulduysa %50 ihtimalle Mağara veya Baraka olur
                            if(rand() % 2 == 0){    
                                siginak = 1; // 1: Mağara
                                printf(">> [TEBRİKLER] Yakınlarda güvenli bir MAĞARA buldun.\n");
                            } else {
                                siginak = 2; // 2: Baraka
                                printf(">> [TEBRİKLER] Terk edilmiş bir BARAKA buldun.\n");
                            }
                        } else {
                           // %70 İhtimalle bulamaz
                           printf(">> [SONUÇ] Sığınak aradın ama uygun bir yer bulamadın.\n");
                        }
                    } else {
                        printf("\n>> [UYARI] Sığınak aramak için 30'dan FAZLA Enerji gerekli.\n");
                    }
                } else {
                    printf("\n>> [BİLGİ] Zaten bir sığınağın var.\n");
                }
                break;

            // --- [E] ENVANTER GÖRÜNTÜLEME ---
            case 'E':
                // Burada printf ile tablo formatında çıktı veriyorum.
                printf("\n.=======================================.\n");
                printf("|           ENVANTER DETAYI             |\n");
                printf("|=======================================|\n");
                printf("| [SAĞLIK]  : %-3d %%                    |\n", saglik);
                printf("| [ENERJİ]  : %-3d %%                    |\n", enerji);
                printf("| [YEMEK]   : %-3d Adet                 |\n", yemek);
                printf("|---------------------------------------|\n");
                printf("| [SIĞINAK] : ");
                // Sığınak değerine göre ekrana ne yazılacağını seçiyorum
                if (siginak == 1) printf("MAĞARA (Güvende)        |\n");
                else if (siginak == 2) printf("BARAKA (Güvende)        |\n");
                else printf("YOK (Tehlikeye Açık)    |\n");
                printf("'======================================='\n");
                break;

            // --- [R] DİNLENME DURUMU ---
            case 'R':
                // Dinlenmek için enerjimin veya sağlığımın eksik olması lazım.
                if (enerji < 100 || saglik < 100) {
                    
                    // Enerji 100'ü geçmesin diye kontrol (Cap Mekanizması)
                    int enerjiArtti = 0; 
                    if (enerji < 100) {
                        enerji += 20;
                        if (enerji > 100) enerji = 100;
                        enerjiArtti = 1;
                    }

                    // Eğer yemek varsa sağlık da artar
                    if (yemek > 0) {
                        yemek--; // Yemeği azalt
                        if (saglik >= 100) {
                            printf("\n>> [DİNLENME] Yemek yedin. Sağlığın doluydu, Enerji yenilendi.\n");
                        } else {
                            saglik += 10;
                            if (saglik > 100) saglik = 100; // Sağlık 100'ü geçemez
                            
                            if (enerjiArtti)
                                printf("\n>> [DİNLENME] Yemek yedin. SAĞLIK ve ENERJİ arttı.\n");
                            else
                                printf("\n>> [DİNLENME] Enerjin doluydu. Yemek sayesinde sadece SAĞLIK arttı.\n");
                        }
                    } else {
                        // Yemek yoksa sadece enerji artar
                        if (enerjiArtti)
                            printf("\n>> [DİNLENME] Yemeksiz uyudun. Karnın aç, sadece ENERJİ arttı.\n");
                        else
                            printf("\n>> [DİNLENME] Hem yemek yok hem enerji dolu. Boşuna zaman harcadın.\n");
                    }
                } else {
                    printf("\n>> [BİLGİ] Turp gibisin! Hem sağlığın hem enerjin dolu.\n");
                }
                break;
            
            // --- [F] TEHLİKE DALGASI (FOR DÖNGÜSÜ KULLANIMI) ---
            case 'F': 
                enerji -= 10; // Tehlikeyle yüzleşmek yorar
                printf("\n!!! TEHLİKE DALGASI BAŞLIYOR !!!\n");
                
                int tehlikeTuru = rand() % 100; 
                
                // Ödevde istenen FOR döngüsü burada. 3 tur boyunca saldırı oluyor.
                for (int i = 1; i <= 3; i++) { 
                    printf("--- [ Dalga %d / 3 ] ---\n", i);
                    hasar = 0; // Her dalgada hasarı sıfırla

                    // %20 ihtimalle DEPREM
                    if (tehlikeTuru < 20) { 
                        printf("Yeryüzü sarsılıyor... (Deprem)\n");
                        if (siginak > 0) {
                            // Sığınak olsa bile depremde taş düşebilir (%50 şans)
                            if (rand() % 100 < 50) {
                                printf(">> Sığınağın sağlam duruyor.\n");
                            } else {
                                hasar = rand() % 10; 
                                printf(">> Tavandan taş düştü! -%d Sağlık\n", hasar);
                            }
                        } else {
                            hasar = (rand() % 10) + 5; 
                            printf(">> Açık alanda dengeni kaybettin! -%d Sağlık\n", hasar);
                        }
                    } 
                    // %80 ihtimalle KURT SÜRÜSÜ
                    else { 
                        printf("Kurtlar saldırıyor...\n");
                        if (siginak == 1) {
                            printf(">> Mağaranın derinliklerine saklandın. (Güvendesin)\n");
                        } else if (siginak == 2) {
                            printf(">> Barakanın kapısını kilitledin. (Güvendesin)\n");
                        } else {
                            // Sığınak yoksa kurtlar saldırır
                            int saldiri = rand() % 15;
                            if (saldiri == 0) {
                                printf(">> Sıyrıldın!\n");
                            } else {
                                hasar = saldiri;
                                printf(">> Isırıldın! -%d Sağlık\n", hasar);
                            }
                        }
                    }
                    
                    saglik -= hasar;
                    // Eğer oyuncu dalga sırasında ölürse döngüyü boşuna devam ettirme, çık.
                    if (saglik <= 0) break; 
                }
                printf("Tehlike dalgası sona erdi.\n");
                break;

            // --- [P] GİZEMLİ SANDIK (DO-WHILE İÇİNDE DO-WHILE) ---
            case 'P': 
            { // Değişken tanımlayabilmek için blok ({}) açtım.
                printf("\n>> Gizemli bir kilitli sandık buldun.\n");
                printf(">> Açmak için 'Z' harfli kilidi kırmalısın.\n");
                
                char kilit;
                // Ödevde istenen ikinci DO-WHILE döngüsü burada.
                // Doğru şifre girilene kadar bu küçük döngü dönmeye devam eder.
                do {
                    printf("Kilit üzerindeki harfi çevir (Tahmin gir): ");
                    
                    // Burada da güvenli giriş (fgets) kullanıyorum
                    char kilitSatir[100];
                    if (fgets(kilitSatir, 100, stdin) == NULL) break;
                    
                    // Boşluk temizleme
                    int m = 0;
                    while (kilitSatir[m] == ' ' || kilitSatir[m] == '\t') m++;
                    kilit = kilitSatir[m];

                    // Harf düzeltme
                    if (kilit >= 'a' && kilit <= 'z') kilit -= 32;

                    if (kilit == 'Z') {
                        printf(">> KİLİT AÇILDI! İçinden konserve çıktı. (+2 Yemek)\n");
                        yemek += 2;
                    } else {
                        // Yanlış girerse ceza ver (Boş enter değilse)
                        if (kilit != '\n' && kilit != '\0') {
                            printf(">> Yanlış harf! Zorlarken yoruldun. (-2 Enerji)\n");
                            enerji -= 2;
                        }
                    }
                    
                    // Enerji biterse döngüden zorla çıkarıyorum ki sonsuz döngü olmasın
                    if (enerji <= 0) break;

                } while (kilit != 'Z'); // Şifre Z değilse dönmeye devam et
            } 
            break;

            // --- [X] ÇIKIŞ ---
            case 'X':
                printf("\n>> Simülasyon sonlandırılıyor... Görüşmek üzere!\n");
                break;

            // --- HATALI TUŞ ---
            default:
                printf("\n>> [HATALI KOMUT] Lütfen listeden geçerli bir seçim yapın.\n");
                break;
        }

        // --- OYUN SONU KONTROLLERİ ---
        // Her komuttan sonra hayati değerleri kontrol ediyorum.
        if (saglik <= 0) {
            printf("\n============================================\n");
            printf("       OYUN BİTTİ - HAYATTA KALAMADIN       \n");
            printf("============================================\n");
            break; // Ana döngüyü kır, programı bitir.
        }
        if (enerji <= 0) { 
            printf("\n============================================\n");
            printf("       OYUN BİTTİ - BİTKİN DÜŞTÜN           \n");
            printf("============================================\n");
             break; // Ana döngüyü kır, programı bitir.
        }

    } while (komut != 'X'); // X komutu gelmediği sürece oyun devam eder.

    return 0; // Program hatasız bitti.
}