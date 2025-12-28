# 🐾 Pet Management System (PMS)
**Hệ thống quản lý thú cưng  - Đồ án C++**

---

##  Kiến trúc Hệ thống (Modular)
Mã nguồn được tổ chức theo mô hình mô-đun để dễ dàng quản lý và mở rộng:

* **Business/**: Chứa logic quản lý chính (`PetManager.cpp`, `PetManager.h`).
* **Core/**: Chứa định nghĩa đối tượng cốt lõi (`Pet.cpp`, `Pet.h`).
* **Menu/**: Chứa các thành phần giao diện menu (`BeautifulMenu.h`, `SubMenu.h`).
* **Utils/**: Chứa các tiện ích xử lý file và hiển thị (`FileHandler.cpp`, `FileHandler.h`,`Utf8Console.h`).
* **Data/**: Nơi lưu trữ cơ sở dữ liệu văn bản (`pets.txt`).

## Biên dịch và Chạy
Hệ thống sử dụng script tự động để đảm bảo việc biên dịch chính xác tất cả các mô-đun.

**Các bước thực hiện:**
1.  Đảm bảo đã cài đặt trình biên dịch **GCC/g++**.
2.  Mở thư mục dự án và chạy file:
    ```bash
    rebuild.bat
    ```
3.  Script sẽ tự động:
    * Dọn dẹp các file rác cũ (`.o`, `.gch`).
    * Quét và biên dịch tất cả file `.cpp` trong các thư mục con.
    * Tạo và khởi chạy file thực thi `doan.exe`.