# Đồng hồ thời gian thực kết hợp báo thức dùng Arduino

## 1. Giới thiệu

Dự án xây dựng đồng hồ thời gian thực có chức năng cài đặt báo thức bằng Arduino. Thời gian được quản lý bởi module RTC DS1307 và hiển thị trên màn hình LCD I2C 16x2. Khi đến giờ báo thức, hệ thống bật còi buzzer và đèn LED; người dùng có thể nhấn nút bất kỳ để tắt báo thức.

## 2. Chức năng chính

- Hiển thị giờ, phút, giây và ngày/tháng/năm.
- Hiển thị giờ báo thức đã cài đặt.
- Cài đặt giờ và phút báo thức.
- Cài đặt giờ, phút và giây hiện tại.
- Bật/tắt chức năng báo thức bằng cách nhấn giữ nút MODE khoảng 2 giây.
- Phát âm thanh và bật LED khi đến giờ báo thức.
- Tắt báo thức bằng cách nhấn một trong các nút hoặc để hệ thống tự tắt sau 30 giây.
- Lưu giờ báo thức và trạng thái bật/tắt vào EEPROM để giữ lại sau khi khởi động lại.

## 3. Linh kiện và phần mềm

- Arduino tương thích với chương trình.
- Module RTC DS1307.
- LCD I2C 16x2.
- 4 nút nhấn: MODE, UP, DOWN, SET.
- 1 đèn LED.
- 1 buzzer.
- Điện trở và dây nối phù hợp.
- Arduino IDE để biên dịch/nạp chương trình.
- Proteus để mô phỏng mạch (nếu sử dụng sơ đồ đi kèm).

## 4. Kết nối chân theo chương trình

| Thiết bị | Chân Arduino |
|---|---|
| Nút MODE | D4 |
| Nút UP | D5 |
| Nút DOWN | D6 |
| Nút SET | D7 |
| LED | D8 |
| Buzzer | D9 |
| RTC DS1307 SDA/SCL | Chân I2C của board Arduino |
| LCD I2C SDA/SCL | Chân I2C của board Arduino |

Các nút nhấn được cấu hình `INPUT_PULLUP`, vì vậy chương trình xem nút được nhấn khi chân tín hiệu ở mức LOW. Chân LED được cấu hình active-low trong code (`LED_ON = LOW`). Địa chỉ LCD đang đặt là `0x20` để mô phỏng Proteus; với một số module LCD I2C thực tế, địa chỉ có thể là `0x27` và cần chỉnh lại cho phù hợp.

## 5. Cách sử dụng

### Chuyển chế độ
Nhấn nhanh nút MODE để lần lượt chuyển qua:
1. Xem giờ.
2. Cài đặt báo thức.
3. Cài đặt thời gian hiện tại.

### Cài đặt báo thức
1. Nhấn MODE đến màn hình `CAI BAO THUC`.
2. Dùng UP/DOWN để tăng hoặc giảm giá trị đang chọn.
3. Nhấn SET để chuyển từ giờ sang phút.
4. Nhấn SET lần nữa để lưu báo thức và trở về màn hình xem giờ.

### Cài đặt thời gian
1. Nhấn MODE đến màn hình `CAI THOI GIAN`.
2. Dùng UP/DOWN để điều chỉnh giờ, phút hoặc giây.
3. Nhấn SET để chuyển giữa các mục.
4. Sau khi xác nhận giây, thời gian mới được ghi vào DS1307.

### Bật/tắt báo thức
- Nhấn giữ MODE khoảng 2 giây để đổi trạng thái báo thức ON/OFF.
- Khi báo thức kêu, nhấn bất kỳ nút nào để tắt.
- Nếu không nhấn nút, báo thức tự tắt sau 30 giây.

## 6. Thư viện cần thiết

Cài đặt hoặc xác nhận Arduino IDE có các thư viện:
- `Wire.h` — giao tiếp I2C.
- `RTClib.h` — giao tiếp với RTC DS1307.
- `LiquidCrystal_I2C.h` — điều khiển LCD I2C.
- `EEPROM.h` — lưu dữ liệu trong EEPROM.

`Wire.h` và `EEPROM.h` thường có sẵn trong bộ công cụ Arduino. `RTClib` và `LiquidCrystal_I2C` có thể cài qua Library Manager; cần dùng phiên bản tương thích với code và phần cứng.

## 7. Thiết lập thời gian ban đầu

Trong file `BaoThucBai32.ino`, biến cấu hình đang được đặt:

```cpp
#define FORCE_SET_TIME 0
```

Khi `FORCE_SET_TIME` là `0`, chương trình chỉ đặt lại thời gian nếu RTC chưa chạy hoặc thời gian đọc được không hợp lệ. Nếu cần ép cập nhật thời gian theo thời điểm biên dịch, đổi thành `1`, biên dịch và nạp lại chương trình một lần, sau đó đổi về `0` và biên dịch/nạp lại để tránh đặt lại thời gian mỗi lần khởi động.

## 8. Kết quả mong đợi

- LCD hiển thị thời gian hiện tại và giờ báo thức.
- Các nút nhấn cho phép thay đổi chế độ và cài đặt thời gian.
- Khi thời gian hiện tại trùng giờ/phút báo thức và báo thức đang bật, buzzer phát âm thanh và LED sáng.
- Báo thức tắt khi nhấn nút hoặc sau 30 giây.
- Giờ báo thức và trạng thái báo thức được lưu trong EEPROM.

## 9. Cấu trúc tệp

- `BaoThucBai32.ino`: mã nguồn Arduino.
- `New Project (1).pdsprj`: tệp dự án Proteus, nếu dùng để mô phỏng.
- Các tệp `.hex`, `.elf`, `.eep`, `.bin`: tệp đầu ra được tạo khi biên dịch; không thay thế cho mã nguồn `.ino`.

## 10. Lưu ý

- Đảm bảo địa chỉ I2C của LCD khớp với phần cứng hoặc mô hình Proteus.
- Kiểm tra cách đấu LED và buzzer phù hợp với cấu hình chân trong chương trình.
- Nếu RTC DS1307 không chạy hoặc hiển thị thời gian không chính xác, kiểm tra nguồn, pin dự phòng và đường I2C.
- Chân I2C cụ thể phụ thuộc vào loại board Arduino đang sử dụng.

## 11. Tác giả

- Họ và tên: ...
- Lớp: ...
- Môn học: ...
