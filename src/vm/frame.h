///Định nghĩa cấu trúc struct frame trong frame.h:
struct frame {
    void *kaddr;                // Địa chỉ vật lý của khung.
    struct page *page;          // Trang ảo liên kết.
    struct list_elem elem;      // Element cho danh sách khung.
};
