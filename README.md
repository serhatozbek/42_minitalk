## 🤖 Minitalk | Ecole 42

Bu repository, iki program arasında UNIX sinyallerini (SIGUSR1 ve SIGUSR2) kullanarak iletişim kuran bir client-server uygulamasını içerir. 42 müfredatının bir parçası olan minitalk projesi, prosesler arası iletişim (Inter-Process Communication - IPC) ve sinyal yönetimi konularını derinlemesine anlamayı hedefler.

#### 🚀 Projenin Amacı ve Yaklaşımı

Bu projenin amacı, bir metin mesajını bir client prosesinden bir server prosesine, yalnızca sinyaller aracılığıyla güvenli ve kayıpsız bir şekilde iletmektir. Proje, standart yaklaşımların aksine, temel versiyonundan itibaren en güvenilir iletişim metodunu benimser.

---

#### ✨ Temel İletişim Protokolü (Güvenli Haberleşme)

**Bu projedeki client ve server, veri kaybını önlemek için çift yönlü bir onay (acknowledgment) mekanizması ile çalışır. İletişim süreci şu adımları izler:**

+ Client Bir Bit Gönderir: client, gönderilecek mesajın sıradaki bitini (0 veya 1) temsil eden bir sinyali (SIGUSR1 veya SIGUSR2) server'a yollar.

+ Client Onay Bekler: Sinyali gönderdikten sonra, client bir sonraki biti göndermeden durur ve server'dan "veriyi aldım" onayını bekler.

+ Server Onaylar: server, gelen biti başarıyla işlediğinde, client'a bir onay sinyali geri gönderir.

+ Döngü Devam Eder: client, bu onayı alınca döngünün başına döner ve gönderilecek bir sonraki biti yollar.

Bu senkronize yapı, "yarış durumu" (race condition) riskini tamamen ortadan kaldırır ve her bir verinin server'a ulaştığını garanti eder. Projenin ana versiyonu bu sağlam temel üzerine kurulmuştur.

---

**⭐ Bonus**: "İletim Tamamlandı" Mesajı

Projenin bonus versiyonu, mevcut güvenli yapıya ek bir özellik daha katar:

Server, client'tan gelen metnin tamamı (yani \0 null karakteri) başarıyla alındığında, kendi terminaline "Mesaj başarıyla alındı!" gibi bir onay mesajı basar.

Bu özellik, server tarafında tüm iletişim sürecinin başarıyla tamamlandığını görsel olarak teyit etmeye yarar ve kullanıcıya geri bildirim sağlar.

#### 🛠️ Nasıl Kullanılır?

Projeyi derlemek için Makefile dosyasındaki hedefleri kullanabilirsiniz.

```Bash

# Repoyu klonla
git clone https://github.com/serhatozbek/42_minitalk.git

# Klasöre git
cd 42_minitalk

# Ana (güvenli) versiyonu derle
make

# VEYA Bonus versiyonu derle
make bonus
```

**Adım 1: Server'ı Çalıştırma**

Bir terminal açın ve derlediğiniz server programını çalıştırın. PID ekrana yazdırılacaktır.

```Bash

./server
Server PID: 2442
Adım 2: Client ile Mesaj Gönderme
İkinci bir terminalde, client programını server'ın PID'si ve mesajınız ile çalıştırın.
```

```Bash

./client 2442 "Bu, güvenli bir şekilde iletilen bir mesajdır."

```
**Sonuç**

Mesajınız, server'ın çalıştığı terminalde harf harf belirecektir. Eğer bonus versiyonunu derlediyseniz, mesajın tamamı alındıktan sonra server terminalinde ek bir onay mesajı göreceksiniz.

---

### ⚠️ Sorumluluk Reddi

 Bu repository'deki çözümler tamamen eğitim ve portföy amaçlıdır. 42'nin onur kuralları (honour code) gereği, Common Core sürecindeki öğrencilerin çözümleri kopyalaması kesinlikle yasaktır. Buradaki kodlar, repodaki projeyi tamamlamış biri olarak gelişimimi göstermek ve gelecekteki projelerim için bir referans noktası oluşturmak amacıyla paylaşılmıştır.

---
