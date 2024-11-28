#include "vm/swap.h"         // Định nghĩa hàm và cấu trúc swap.
#include "vm/page.h"         // Kết nối swap với page.
#include "devices/block.h"   // Sử dụng block device để lưu swap.
#include "threads/vaddr.h"   // Địa chỉ ảo, hỗ trợ phân trang.
#include "threads/synch.h"   // Đồng bộ khi thao tác với swap.
#include <bitmap.h>          // Sử dụng bitmap để quản lý không gian swap.
#include <stdbool.h>         // Kiểu boolean.

//Ghi vao swap
void swap_out(struct page *page) {
    // Ghi dữ liệu từ khung vào không gian swap.
    block_write(swap_block, page->swap_index, page->frame->kaddr);
    page->in_swap = true;
}

//Doc tu swap
void swap_in(struct page *page) {
    // Đọc dữ liệu từ không gian swap vào khung.
    block_read(swap_block, page->swap_index, page->frame->kaddr);
    page->in_swap = false;
}
