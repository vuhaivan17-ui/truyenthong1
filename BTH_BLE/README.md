# Điều khiển bật/tắt đèn qua Bluetooth BLE

## 1. Giới thiệu

Bài tập thực hiện điều khiển trạng thái đèn bằng điện thoại thông qua kết nối Bluetooth Low Energy (BLE). Người dùng gửi giá trị từ ứng dụng BLE trên điện thoại để yêu cầu bật hoặc tắt đèn.

## 2. Mục tiêu

- Tìm hiểu cách kết nối thiết bị ngoại vi bằng Bluetooth BLE.
- Thực hiện ghi dữ liệu từ điện thoại đến thuộc tính BLE của thiết bị.
- Điều khiển trạng thái đèn theo giá trị nhận được.
- Kiểm tra và quan sát kết quả bật/tắt đèn trên hệ thống.

## 3. Công cụ và giao thức

- Thiết bị điều khiển: thiết bị có hỗ trợ Bluetooth BLE.
- Thiết bị thao tác: điện thoại thông minh.
- Ứng dụng: ứng dụng BLE có chức năng đọc/ghi thuộc tính.
- Giao thức kết nối: Bluetooth Low Energy (BLE).

## 4. Nguyên lý hoạt động

1. Bật Bluetooth trên điện thoại và kết nối với thiết bị BLE.
2. Trong danh sách dịch vụ, tìm thuộc tính dùng để nhận lệnh điều khiển đèn.
3. Chọn chức năng **Write Value** để ghi giá trị điều khiển.
4. Gửi giá trị tương ứng:
   - `0`: yêu cầu tắt đèn.
   - `1`: yêu cầu bật đèn.
5. Thiết bị nhận giá trị và cập nhật trạng thái đèn theo chương trình được cài đặt.

**Lưu ý:** Các ảnh minh họa cho thấy ứng dụng đang chọn kiểu dữ liệu `UTF8`. Nếu firmware của thiết bị xử lý giá trị số nguyên hoặc byte, cần chọn đúng kiểu dữ liệu tương ứng (ví dụ `UnsignedInt` hoặc `ByteArray`) để giá trị gửi đi khớp với chương trình. Tên dịch vụ/thuộc tính hiển thị trong ứng dụng không đủ để xác định chắc chắn UUID và chức năng thực tế của chúng; cần đối chiếu với firmware của thiết bị.

## 5. Các bước thực hiện

1. Cấp nguồn cho thiết bị BLE.
2. Mở ứng dụng BLE trên điện thoại.
3. Quét và kết nối với thiết bị.
4. Mở dịch vụ và thuộc tính nhận dữ liệu điều khiển.
5. Ghi `0`, nhấn **Write** và kiểm tra đèn tắt.
6. Ghi `1`, nhấn **Write** và kiểm tra đèn bật.
7. Ghi lại kết quả kiểm tra.

## 6. Kết quả mong đợi

| Giá trị gửi | Trạng thái đèn mong đợi |
|---|---|
| `0` | Tắt |
| `1` | Bật |

Kết quả chỉ được xác nhận khi đèn thực tế thay đổi trạng thái đúng theo giá trị gửi từ điện thoại.

## 7. Kết luận

Bài tập minh họa việc gửi dữ liệu điều khiển từ điện thoại đến thiết bị qua Bluetooth BLE. Với quy ước `0` là tắt và `1` là bật, người dùng có thể kiểm tra việc truyền dữ liệu và phản hồi của thiết bị. Để hệ thống hoạt động chính xác, kiểu dữ liệu ghi trên ứng dụng phải phù hợp với cách firmware đọc dữ liệu.

## 8. Minh họa

- Ảnh 1: Ghi giá trị `0` để yêu cầu tắt đèn.
- Ảnh 2: Ghi giá trị `1` để yêu cầu bật đèn.
