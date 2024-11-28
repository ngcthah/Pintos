struct page {
    void *vaddr;                // Địa chỉ ảo của trang.
    struct frame *frame;        // Khung bộ nhớ vật lý tương ứng.
    struct file *file;          // File ánh xạ, nếu có.
    size_t file_offset;         // Offset trong file.
    size_t read_bytes;          // Số byte cần đọc từ file.
    size_t zero_bytes;          // Số byte cần điền 0.
    bool writable;              // Trang này có thể ghi không.
    bool in_swap;               // Cờ cho biết trang có trong swap không.
    size_t swap_index;          // Chỉ số trang trong swap, nếu có.
    struct hash_elem hash_elem; // Element dùng cho hash table.
};
