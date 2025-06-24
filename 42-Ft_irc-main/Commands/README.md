# IRC Server Projesi Teknik Dokümantasyonu

## 1. Projeye Giriş

Bu proje, 42 okulunun "ft_irc" adlı projesine dayanarak geliştirilmiş, C++98 standartlarına uygun, modüler yapıya sahip bir IRC sunucusudur. Proje, socket programlama, event-driven mimari, komut yorumlama, kanal bazlı mesajlaşma sistemleri ve mod tabanlı kanal kontrolü gibi çekirdek sistemleri kapsar.

Amaç: Basit bir IRC sunucusu yazmak, client'lardan gelen komutlara yanıt vermek, birden fazla istemciyi aynı anda yönetmek ve kanal mantığını desteklemektir. Ayrıca C++ dilinin sınırları içerisinde nesne tabanlı yapılarla sistemi daha okunabilir ve geliştirilebilir kılmak hedeflenmiştir.

---

## 2. Socket Nedir?

**Socket**, bir bilgisayar üzerinde veya bilgisayarlar arasında iletişim kurmak için kullanılan bir endpoint'tir. Socket yapısı, işletim sisteminin sunduğu bir API üzerinden iki uç arasında veri alışverişi yapılmasını sağlar.

Nerelerde kullanilir: 

Bu projede **TCP (Transmission Control Protocol)** soketleri kullanılmıştır. TCP, bağlantı tabanlıdır ve veri iletiminde sıralama ve güvenilirlik sağlar. Alternatif olarak UDP (User Datagram Protocol) kullanılabilirdi, fakat IRC gibi mesaj bazlı, oturum içeren sistemlerde aşağıdaki karşılaştırmadan da görüleceği üzere TCP daha uygun bir tercihtir:

| Özellik        | TCP                          | UDP                      |
|----------------|-------------------------------|---------------------------|
| Bağlantı       | Bağlantılı (connection-based) | Bağlantısız              |
| Güvenilirlik   | Veri kaybı yaşanmaz           | Paketler kaybolabilir     |
| Sıralama       | Garantili                     | Yok                       |
| Performans     | Daha yavaş (güvenlik sebebiyle) | Daha hızlı                |

IRC protokolü kullanıcı oturumu ve mesaj güvenliği gerektirdiğinden, **TCP** tercih edilmiştir.

### 2.1 Socket Kurulumu

Bu projede TCP soketleri aşağıdaki gibi oluşturulmuştur:

```cpp
int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
```

- `AF_INET` → IPv4
- `SOCK_STREAM` → TCP
- `0` → Varsayılan protokol (TCP)

Sunucu soketi `bind()` ile belirli bir port'a bağlanır, `listen()` ile yeni bağlantılar beklenir ve `accept()` ile gelen bağlantı kabul edilir.

---

## 3. Socket Haberleşmesi Nasıl Sağlanıyor?

Socket üzerinden haberleşme sağlarken bu projede `poll()` fonksiyonu tercih edilmiştir. `poll()`, sistemin birden fazla istemci soketini aynı anda dinlemesine izin verirken tek bir thread içinde çalışmayı mümkün kılar.

Alternatif olarak `select()` veya Linux'a özel `epoll()` sistem çağrıları da kullanılabilir:

| Yöntem    | Açıklama                                                                 |
|-----------|--------------------------------------------------------------------------|
| select()  | En eski yöntemdir. Dosya tanımlayıcı sınırı (FD_SETSIZE) ile sınırlıdır. |
| poll()    | Daha esnektir, dosya tanımlayıcı sınırı yoktur, dizilerle çalışır.       |
| epoll()   | Yalnızca Linux sistemlerde çalışır, çok daha ölçeklenebilir ve hızlıdır. |

`poll()`, bu proje için yeterli performans ve taşınabilirlik sağladığından tercih edilmiştir.

### 3.0 İstemci Bağlantıları (nc / HexChat)

İstemciler ("netcat" veya HexChat gibi) sunucuya TCP bağlantısı kurarak mesajlarını socket üzerinden gönderirler. Bu mesajlar, sunucu tarafında `recv()` fonksiyonu ile okunur ve `Commands::processMessage()` fonksiyonuna aktarılarak analiz edilir.

#### nc ile Bağlantı:

```bash
nc 127.0.0.1 4444
PASS 4242
NICK Emirhan
USER Emirhan 0 * :Real Name
JOIN #kanal
PRIVMSG #kanal :Selam millet
```

#### HexChat ile Bağlantı:

1. Sunucu olarak `127.0.0.1` girilir.
2. Bağlantı portu olarak sunucu portu (orn. `4444`) girilir.
3. Şifre (password) alanına `4242` girilir.
4. HexChat istemcisine komutlar terminal gibi girilir: `/join`, `/privmsg`, `/kick`, vb.

#### 📡 HexChat Üzerinden Bağlantı ve Girdi Kuralları

IRC istemcileri arasında en yaygın grafik arayüze sahip olan **HexChat**, komutları ve mesajları özel bir biçimde işler. Bu nedenle HexChat ile test yaparken şu kurallar göz önünde bulundurulmalıdır:

##### 1. Komutlar `:` karakteri olmadan yazılmalıdır

HexChat’te kullanıcılar komutları terminal ekranındaki komut satırına `/` ile başlatarak yazar. Örneğin:

```bash
/join #kanal
/part #kanal
/msg #kanal Merhaba!
```

IRC protokolünde ise bu komutlar genellikle istemci tarafından şu şekilde sunucuya iletilir:

```bash
JOIN #kanal\r\n
PART #kanal\r\n
PRIVMSG #kanal :Merhaba!\r\n
```

Yani HexChat kendisi `:` ekler. Bu yüzden `PRIVMSG` gibi komutlarda sunucuda `:` işareti beklenmeli, ama kullanıcıdan manuel olarak istenmemelidir.

##### 2. Komut ile parametre arasında sadece bir boşluk olur

HexChat `/mode`, `/kick`, `/invite` gibi komutlarda parametreleri otomatik ayrıştırır. Örneğin:

```irc
/mode #kanal +o Emirhan
```

Bu HexChat tarafından şu şekilde sunucuya gönderilir:

```
MODE #kanal +o Emirhan\r\n
```

##### 3. Şifreli giriş `/pass` kullanılarak yapılabilir

HexChat’te “password” alanına şifre yazıldığında bağlantı sonrası istemci şu komutu otomatik gönderir:

```
PASS <şifre>\r\n
```

Veya elle terminalden:

```irc
/pass 4242
```

##### 4. JOIN komutları bazen kanala girmeden önce `WHO` gönderir

HexChat bazen `JOIN` sonrası otomatik olarak `WHO` gönderir. `WHO` için kanal daha oluşmadan çağrı gelirse, bu hata değildir.

##### 5. `TOPIC` ve `MODE` davranışları

HexChat GUI’si üzerinden kanal başlığı değiştirildiğinde sunucuya şu komut gider:

```
TOPIC #kanal :Yeni başlık\r\n
```

#### ✅ Özet: HexChat İstemci Davranışı

| HexChat Aksiyonu          | Gönderilen Ham Komut                    | Sunucuda Beklenen |
|---------------------------|-----------------------------------------|-------------------|
| `/join #kanal`            | `JOIN #kanal`                           | `JOIN` fonksiyonu |
| `/msg #kanal selam`       | `PRIVMSG #kanal :selam`                | `PRIVMSG`         |
| GUI'den topic değişimi    | `TOPIC #kanal :yeni başlık`            | `TOPIC`           |
| GUI'den kick              | `KICK #kanal kullanıcı :neden`         | `KICK`            |
| Şifreli giriş             | `PASS 4242`                             | `PASS`            |


### 3.1 Sunucu Çalışma Mantığı

1. **Sunucu socket'i oluşturulur.**
2. **bind()** ile IP:PORT adresine bağlanır.
3. **listen()** ile dinlemeye başlanır.
4. **poll()** ile birden fazla istemci socket'i beklenir.
5. **accept()** ile yeni istemciler kabul edilir.
6. Veri alınır ve `recv()` fonksiyonu ile okunur.
7. Gelen mesaj `processMessage()` fonksiyonuna aktarılır.

### 3.2 poll() Kullanımı

```cpp
poll(pollfds, nfds, -1); // -1: sonsuz bekleme
```

- `pollfds` dizisi: Tüm client soketlerini içerir
- `revents`: Veri geldiyse kontrol edilir

Bu mimari sayesinde server tek bir thread ile yüzlerce istemciyi yönetebilir.

---

## 4. Komutların İşlenmesi

Tüm istemci mesajları `Commands::processMessage()` fonksiyonuna gelir. Bu fonksiyon, gelen mesajı parçalar ve hangi IRC komutu geldiyse ilgili handler'a yollar:

```cpp
if (command == "JOIN")
    joinCommand(...);
```

### Örnek: JOIN Komutunun İşlenme Sücreci

1. Kullanıcı terminal/HexChat üzerinden `JOIN #kanal` komutunu gönderir.
2. Sunucu `recv()` ile bu mesajı alır.
3. `Server::receiveMessage()` çağrılır ve mesaj `processMessage()`'a aktarılır.
4. Komut "JOIN" olarak tespit edilir ve `joinCommand()` fonksiyonu çağrılır.
5. Fonksiyon şunları kontrol eder:
   - PASS komutu önceden girilmiş mi?
   - Kanal ismi `#` ile başlıyor mu?
   - Kanal zaten var mı, yoksa oluşturulacak mı?
   - Şifre, limit, +i gibi modlar etkin mi?
6. Koşullar sağlanırsa client ID kanal dizisine eklenir.
7. `JOIN` mesajı diğer kullanıcılara yayınlanır.

Bu işlem aynı zamanda test edilebilirlik için iyi bir akış çıkarır. Benzer adımlar `PRIVMSG`, `PART`, `KICK` gibi komutlar için de geçerlidir.

Her komut modüler halindedir:

- `Pass.cpp`, `Nick.cpp`, `User.cpp`
- `Join.cpp`, `Part.cpp`, `Kick.cpp`
- `Mode.cpp`, `Topic.cpp`, `Invite.cpp`

Ve tümü socket üzerinden mesajları doğrudan döner:

```cpp
send(client_fd, response.c_str(), response.size(), 0);
```

---

## 5. Kanal Sistemi ve Kullanıcı Takibi

Sunucu kanal yapısını ve istemcileri aşağıdaki veri yapılarıyla yönetir:

### 5.1 Kanallar
- `std::map<std::string, std::set<int> > channels`
- Kanal adına karşı socket'ler tutulur

### 5.2 Nickname - Socket Eşleşmesi
- `std::map<int, std::string> nicknames`
- Her client socket'ine karşılık gelen nick tutulur

Bu sayede istemcilerin kimlikleri ve katıldıkları kanallar kolayca izlenebilir.

---

## 6. MODE Sistemi

`MODE` komutu kanal ayarını yapar:

- `+i`: Davetle giriş (invite-only)
- `+k`: Kanal Şifresi
- `+l`: Kullanıcı limiti
- `+o`: Operatör atama
- `+t`: Topic değiştirme kilidi

### MODE Parametre Tablosu

| Mod  | Açıklama                                | Parametre Gerekir mi? |
|------|------------------------------------------|------------------------|
| +i   | Davet ile giriş                          | Hayır                 |
| +k   | Kanal şifresi                            | Evet (`şifre`)         |
| +l   | Maksimum kullanıcı limiti                | Evet (`sayaç`)          |
| +o   | Kanal operatörlüğü                       | Evet (`nickname`)      |
| +t   | Sadece operatörlerin topic değiştirmesi  | Hayır                 |

Her mod için `Modes/` klasöründe bir fonksiyon bulunur:

```cpp
Modes::setKey(...);
Modes::setLimit(...);
Modes::setOperator(...);
```

`processMode()` fonksiyonu birden fazla modu tek seferde işleyebilir:

```bash
/mode #kanal +kolt nick 3 sifre
```

---

## 7. Komut Modülerinin Parçalanması (Refactor Yapısı)

Projenin ilk versiyonunda tüm komutlar `Commands.cpp` içindeydi. Zamanla okunabilirlik ve modüler arındırma adına aşağıdaki gibi dağıtıldı:

```
Commands/
├── Join.cpp / Join.hpp
├── Kick.cpp / Kick.hpp
├── Topic.cpp / Topic.hpp
...
Modes/
├── Invite.cpp / Invite.hpp
├── Limit.cpp / Limit.hpp
...
```

Her komut ve mod ayrı olarak test edilebilir, geliştirilebilir ve yeniden kullanılabilir hale getirildi.

---

## 8. Projenin Son Durumu

- [x] Socket yapısı ve event-driven poll() mimarisi kuruldu
- [x] Komutlar yorumlayıcıya bağlandı
- [x] Kanal sistemi oturtuldu
- [x] `MODE` komutları modülerle ayrıldı
- [x] Detaylı test planları yazıldı
- [x] HexChat ve nc istemcileriyle doğrudan test edildi

---

## 9. Geliştirme Potansiyeli (Bonuslar)

- `WHO`, `NOTICE`, `AWAY`, `PING`, `PONG` gibi destekleyici komutlar eklenebilir
- Kanal kullanıcı listesi ve aktiflik kontrol mekanizması eklenebilir
- SSL/TLS desteği ile güvenlik artırılabilir
- Sunucu oturum loglaması, zaman damgası gibi iyileştirmeler yapılabilir

---

## 10. Son Söz

Bu proje sayesinde:
- **Socket haberleşmesi**,
- **Sunucu taraflı poll() yönetimi**,
- **IRC protokolüne uygun parsing**,
- **Dinamik C++ yapısı ve modüler refactoring** detaylı olarak öğrenilmiştir.

Bu doküman, projeyi anlamak, bakım yapmak ya da devralmak isteyen herkes için başvuru kaynağı olarak yazılmıştır.

Hazırlayanlar: Melis Portakal, Emirhan Akman 

