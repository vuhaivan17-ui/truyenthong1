# Bài thực hành MQTT – Điều khiển LED với ESP32-S3 và Home Assistant

## 1. Giới thiệu

Dự án thực hiện điều khiển LED tích hợp trên ESP32-S3 thông qua giao thức MQTT. Thiết bị kết nối Wi-Fi, kết nối đến MQTT broker và nhận lệnh bật/tắt LED. Trạng thái LED được gửi lại broker để Home Assistant hiển thị.

Dự án gồm hai phần:
- **Bài 12.2 – Điều khiển LED qua MQTT:** nhận lệnh `ON`/`OFF` và phản hồi trạng thái.
- **Bài 12.3 – MQTT Retain:** sử dụng retained message để lưu trạng thái LED, đồng thời gửi trạng thái kết nối bằng LWT (Last Will and Testament).

File `YAML.txt` chứa cấu hình MQTT cho Home Assistant, bao gồm các sensor của bài 12.1 và switch cho bài 12.2, 12.3.

## 2. Công nghệ sử dụng

- Board: ESP32-S3.
- Ngôn ngữ: C++ trên Arduino IDE.
- Kết nối mạng: Wi-Fi.
- Giao thức nhắn tin: MQTT.
- Thư viện Arduino: `WiFi.h`, `WiFiClient.h`, `PubSubClient.h`.
- Giao diện giám sát/điều khiển: Home Assistant.
- LED: LED RGB tích hợp, điều khiển qua `neopixelWrite()` tại GPIO 48.

## 3. Chức năng

### Bài 12.2 – Điều khiển LED qua MQTT

- Kết nối ESP32-S3 vào Wi-Fi.
- Kết nối MQTT broker bằng địa chỉ IP, cổng và tài khoản được cấu hình trong code.
- Đăng ký nhận lệnh từ topic điều khiển.
- Nhận `ON` để bật LED, `OFF` để tắt LED.
- Gửi trạng thái hiện tại `ON` hoặc `OFF` lên topic trạng thái.
- Tự kết nối lại MQTT khi mất kết nối.

### Bài 12.3 – MQTT Retain

Ngoài các chức năng cơ bản ở bài 12.2, chương trình:
- Hỗ trợ lệnh `ON`, `OFF` và `TOGGLE`.
- Gửi trạng thái LED với cờ **retain = true** để broker lưu lại trạng thái mới nhất.
- Cấu hình LWT để broker có thể thông báo `OFFLINE` nếu thiết bị mất kết nối bất thường.
- Gửi `ONLINE` khi kết nối MQTT thành công.
- Gửi thông báo `ESP BOOT / RECONNECT` lên topic ghi chú, không retain.
- Gửi lại trạng thái LED sau khi kết nối MQTT thành công.

## 4. MQTT topics

ID được dùng trong các topic của mã nguồn hiện tại là `10124345`.

| Bài | Topic | Mục đích |
|---|---|---|
| 12.2 | `iot/lab2/10124345/cmd` | Nhận lệnh bật/tắt LED |
| 12.2 | `iot/lab2/10124345/state` | Công bố trạng thái LED |
| 12.3 | `iot/lab3/10124345/cmd` | Nhận lệnh `ON`, `OFF`, `TOGGLE` |
| 12.3 | `iot/lab3/10124345/state` | Công bố trạng thái LED, có retain |
| 12.3 | `iot/lab3/10124345/note` | Thông báo khởi động/kết nối lại |
| 12.3 | `iot/lab3/10124345/lwt` | Trạng thái kết nối `ONLINE`/`OFFLINE` |

## 5. Chuẩn bị

1. Cài đặt Arduino IDE.
2. Cài đặt board package ESP32 tương thích với ESP32-S3.
3. Cài thư viện **PubSubClient** qua Library Manager.
4. Chuẩn bị Wi-Fi mà ESP32-S3 có thể kết nối.
5. Chuẩn bị MQTT broker và tài khoản đăng nhập.
6. Cấu hình Home Assistant và tích hợp MQTT.

## 6. Cấu hình trước khi chạy

Mở file `.ino` tương ứng và cập nhật thông tin Wi-Fi, MQTT broker, cổng và thông tin xác thực theo môi trường của bạn.

- `ssid`: tên mạng Wi-Fi.
- `password`: mật khẩu Wi-Fi.
- `mqtt_server`: địa chỉ IP máy chạy MQTT broker.
- `mqtt_port`: cổng MQTT, trong mã hiện tại là `1883`.
- `mqtt_user` và `mqtt_pass`: tài khoản MQTT.
- `student_id`: mã định danh dùng trong topic.

**Bảo mật:** Không chia sẻ hoặc đẩy mật khẩu Wi-Fi/MQTT thật lên GitHub. Nên thay thông tin nhạy cảm trong mã nguồn bằng giá trị mẫu trước khi công khai repository.

## 7. Cấu hình Home Assistant

File `YAML.txt` khai báo:
- Hai sensor nhiệt độ và độ ẩm của bài 12.1, đọc dữ liệu JSON từ `iot/lab1/10124345/sensor`.
- Switch điều khiển LED bài 12.2.
- Switch LED bài 12.3, sử dụng topic LWT để hiển thị tình trạng thiết bị.

Đưa phần cấu hình vào đúng khu vực cấu hình MQTT của Home Assistant theo phiên bản đang sử dụng, sau đó kiểm tra cấu hình và tải lại hoặc khởi động lại Home Assistant theo yêu cầu.

Lưu ý: trong `YAML.txt`, hai switch được đặt dưới khóa `switch:`. Khi chỉnh sửa hoặc ghép vào cấu hình hiện có, cần giữ đúng cấu trúc và thụt lề YAML.

## 8. Cách chạy và kiểm tra

### Bài 12.2
1. Mở `BTH12.2_MQTT.ino` bằng Arduino IDE.
2. Cập nhật thông tin Wi-Fi và MQTT.
3. Chọn đúng board ESP32-S3 và cổng nạp.
4. Biên dịch, nạp chương trình và mở Serial Monitor ở tốc độ `115200`.
5. Kiểm tra log kết nối Wi-Fi/MQTT.
6. Từ Home Assistant hoặc MQTT client, gửi `ON` và `OFF` đến topic `iot/lab2/10124345/cmd`.
7. Kiểm tra LED và trạng thái ở topic `iot/lab2/10124345/state`.

### Bài 12.3
1. Mở `BTH12.3_MQTT.ino`, cập nhật cấu hình rồi nạp vào ESP32-S3.
2. Kiểm tra các topic `cmd`, `state`, `note` và `lwt`.
3. Gửi `ON`, `OFF` hoặc `TOGGLE` đến topic điều khiển.
4. Xác nhận trạng thái LED được publish với retain.
5. Kiểm tra `ONLINE` khi thiết bị kết nối và `OFFLINE` khi broker xác định thiết bị mất kết nối bất thường.
6. Khởi động lại hoặc kết nối lại MQTT client để kiểm tra retained state.

## 9. Kết quả mong đợi

- ESP32-S3 kết nối Wi-Fi và MQTT broker thành công.
- Lệnh MQTT điều khiển được LED RGB tích hợp.
- Topic trạng thái phản ánh trạng thái LED.
- Ở bài 12.3, broker lưu trạng thái LED gần nhất bằng retained message.
- Home Assistant hiển thị các switch và trạng thái thiết bị theo cấu hình MQTT.

## 10. Danh sách tệp

- `BTH12.2_MQTT.ino`: chương trình điều khiển LED qua MQTT.
- `BTH12.3_MQTT.ino`: chương trình điều khiển LED dùng retain và LWT.
- `YAML.txt`: cấu hình MQTT cho Home Assistant.

## 11. Lưu ý khi xử lý lỗi

- Nếu không kết nối được Wi-Fi, kiểm tra SSID, mật khẩu và vùng phủ sóng.
- Nếu không kết nối được MQTT, kiểm tra IP broker, cổng, tài khoản, mật khẩu và firewall.
- Nếu Home Assistant không điều khiển được LED, kiểm tra topic và payload có khớp chính xác với code hay không.
- Nếu LED không sáng, xác nhận board có LED RGB tích hợp tương thích với GPIO 48 và hỗ trợ `neopixelWrite()`.
- Nếu trạng thái LWT không đổi ngay, lưu ý broker chỉ phát thông báo mất kết nối sau khi phát hiện phiên MQTT bị ngắt bất thường; đây không phải lúc nào cũng diễn ra tức thời.

## 12. Thông tin sinh viên

- Họ và tên: ...
- Mã sinh viên: 10124345
- Lớp: ...
- Môn học: ...
