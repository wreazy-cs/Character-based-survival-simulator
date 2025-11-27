# 🏕️ Karakter Tabanlı Hayatta Kalma Simülatörü

[![C](https://img.shields.io/badge/Language-C-blue.svg)](https://en.wikipedia.org/wiki/C_(programming_language))
[![License](https://img.shields.io/badge/License-MIT-green.svg)](LICENSE)
[![University](https://img.shields.io/badge/University-Kırklareli-red.svg)](https://www.klu.edu.tr/)

Terminal tabanlı, interaktif bir hayatta kalma oyunu. C dilinin temel yapılarını (döngüler, karar yapıları, rastgelelik) kullanarak geliştirilmiştir.

## 📋 İçindekiler

- [Oyun Hakkında](#-oyun-hakkında)
- [Özellikler](#-özellikler)
- [Kurulum](#-kurulum)
- [Nasıl Oynanır](#-nasıl-oynanır)
- [Komutlar](#-komutlar)
- [Teknik Detaylar](#-teknik-detaylar)
- [Ekran Görüntüleri](#-ekran-görüntüleri)
- [Geliştirici Bilgileri](#-geliştirici-bilgileri)

## 🎮 Oyun Hakkında

Bu proje, Kırklareli Üniversitesi Yazılım Mühendisliği Bölümü "Algoritma ve Programlama 1" dersi için geliştirilmiş bir terminal oyunudur. Oyuncu, vahşi doğada hayatta kalmaya çalışırken kaynak yönetimi, risk alma ve stratejik düşünme becerilerini kullanır.

### Ana Mekanikler
- **Kaynak Yönetimi**: Sağlık, enerji ve yemek dengesi
- **Rastgelelik**: Her oyun farklı deneyimler sunar
- **Risk vs Ödül**: Her eylem bir bedel veya kazanç getirir
- **Hayatta Kalma**: Tehlikelerden korunma ve barınma arayışı

## ✨ Özellikler

- 🎯 **6 Farklı Eylem**: Avlanma, sığınak arama, dinlenme, tehlike dalgaları, gizem ve envanter
- 🏠 **Sığınak Sistemi**: Mağara ve baraka bulma mekanikleri
- ⚔️ **Tehlike Dalgaları**: Deprem ve kurt sürüsü saldırıları
- 🔐 **Şifreli Sandıklar**: Mini bulmaca çözme
- 📊 **Detaylı İstatistikler**: Gerçek zamanlı durum takibi
- 🎲 **Dinamik Rastgelelik**: Her oyun benzersiz deneyim
- 💾 **Güvenli Girdi Yönetimi**: Hata toleranslı kullanıcı girişi

## 🚀 Kurulum

### Gereksinimler
- GCC veya herhangi bir C derleyicisi
- Terminal/Komut İstemi

### Derleme

**Linux/Mac:**
```bash
gcc -o survival_game main.c
./survival_game
```

**Windows (MinGW):**
```cmd
gcc -o survival_game.exe main.c
survival_game.exe
```

**Windows (Visual Studio):**
```cmd
cl main.c
main.exe
```

## 🎯 Nasıl Oynanır

### Oyun Kuralları

1. **Sağlık ve Enerji** 0'a düşerse oyun biter
2. Her eylem **enerji maliyeti** gerektirir
3. Sığınaklar **kurtlardan %100 koruma** sağlar
4. Depremler sığınaklara bile **hasar verebilir**
5. Yanlış şifre girimleri **enerji kaybettirir**

### Başlangıç Değerleri
- 💚 Sağlık: 100%
- ⚡ Enerji: 100%
- 🍖 Yemek: 0 adet
- 🏠 Sığınak: Yok

## 🎮 Komutlar

| Komut | Eylem | Maliyet | Açıklama |
|-------|-------|---------|----------|
| **A** | Avlan | -15 Enerji | Tavşan avla, %60 başarı şansı |
| **S** | Sığınak Ara | -30 Enerji | Mağara veya baraka bul, %30 şans |
| **R** | Dinlen | Yemek | Sağlık ve enerji yenile (+20 Enerji, +10 Sağlık) |
| **F** | Tehlike Modu | -10 Enerji | 3 dalgalık tehlikeyle mücadele |
| **P** | Gizem | Değişken | Şifreli sandık aç, konserve kazan |
| **E** | Envanter | Ücretsiz | Detaylı durum görüntüle |
| **X** | Çıkış | - | Oyunu sonlandır |

### ⚠️ Önemli Notlar
- Eylem maliyetinden **FAZLA** enerjiye sahip olmalısınız!
  - Örnek: Avlanmak için en az **16 enerji** gerekir (15 değil)
- Sığınaklar bulunduktan sonra **kalıcıdır**
- Tehlike modunda dalga sırasında ölüm **oyunu bitirir**

## 🛠️ Teknik Detaylar

### Kullanılan C Yapıları

```c
/* Ana yapılar ve kullanım nedenleri */

1. DO-WHILE Döngüsü
   └─> Oyun menüsünün en az bir kez çalışması için

2. FOR Döngüsü
   └─> Tehlike modunda 3 dalgalı saldırı sistemi için

3. SWITCH-CASE
   └─> Kullanıcı komutlarını (A, S, R, vb.) yönetmek için

4. WHILE Döngüsü + FGETS
   └─> Güvenli girdi alma, boşluk/tab hatalarını önleme

5. RAND() & SRAND()
   └─> Her oyunda benzersiz olaylar üretme
```

### Kod Organizasyonu

- **Değişken Yönetimi**: Global değil, main içinde yerel değişkenler
- **Input Sanitization**: Buffer overflow koruması
- **Cap Mekanizması**: Sağlık/Enerji 100'ü geçemez
- **Early Exit**: Ölüm durumunda döngü kırılması

### Güvenlik Özellikleri

```c
// Buffer overflow koruması
char satir[100];
fgets(satir, 100, stdin);

// Boşluk/Tab temizleme
while (satir[k] == ' ' || satir[k] == '\t') k++;

// Büyük-küçük harf dönüşümü
if (komut >= 'a' && komut <= 'z') komut -= 32;
```

## 📸 Ekran Görüntüleri

```
      /\                                                       /\
     /  \      KARAKTER TABANLI HAYATTA KALMA SİMÜLATÖRÜ      /  \
    /    \     -----------------------------------------     /    \
   /      \                                                 /      \
  /  /\    \        [ YAZILIM MÜHENDİSLİĞİ BÖLÜMÜ ]        /    /\  \
======================================================================

------------------------------------------------------------
DURUM RAPORU -> [ SAĞLIK: 85 % | ENERJİ: 70 % ]
KOMUTLAR     -> [A] [S] [E] [R] [F] [P] [X]
------------------------------------------------------------
```

## 🎓 Geliştirici Bilgileri

**Öğrenci**: Samet Muhammed Ali Şafak  
**Öğrenci No**: 1250505013  
**Üniversite**: Kırklareli Üniversitesi  
**Bölüm**: Yazılım Mühendisliği  
**Ders**: Algoritma ve Programlama 1

## 📝 Notlar

- Oyun **seed mekanizması** ile her açılışta farklı deneyim sunar
- **ASCII sanatı** ile terminal estetiği sağlanmıştır
- Kod içi **Türkçe yorumlar** öğrenme amaçlıdır
- Input validation ile **kullanıcı hataları** minimize edilmiştir

## 🤝 Katkıda Bulunma

Bu proje eğitim amaçlı geliştirilmiştir. Öneriler için:
1. Issue açabilirsiniz
2. Fork edip geliştirme yapabilirsiniz
3. Pull request gönderebilirsiniz

## 📜 Lisans

Bu proje MIT lisansı altında sunulmaktadır. Detaylar için `LICENSE` dosyasına bakınız.
