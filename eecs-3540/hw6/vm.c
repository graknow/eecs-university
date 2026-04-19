#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE         (10)
#define PAGE_TABLE_SIZE     (256)
#define NUMBER_OF_FRAMES    (256)
#define FRAME_SIZE          (256)
#define TLB_SIZE            (16)
/* an entry in the tlb */
typedef struct tlb_entry
{
    int page_number;
    int frame_number;
    int valid;
} tlb_entry_t;

FILE *address_file;
FILE *backing_store;
/* buffer for reading logical addresses */
char buffer[BUFFER_SIZE];
/* representation of physical memory */
signed char *physical_memory;
/* page table */
int page_table[PAGE_TABLE_SIZE];
/* list of free frames */
int free_frame_list[NUMBER_OF_FRAMES];
/* the tlb */
tlb_entry_t tlb[TLB_SIZE];
int tlb_usage_priority[TLB_SIZE];

int main(int argc, char *argv[])
{
    if (argc <= 2 || argc >= 4)
    {
        fprintf(stderr, "Insufficient parameters.  Correct usage: ./vm <Backing Store>.bin <Address List>.txt");
        exit(1);
    }

    backing_store = fopen(argv[1], "rb");
    if (!backing_store)
    {
        fprintf(stderr, "Backing store at '%s' could not be opened", argv[1]);
        exit(2);
    }
    address_file = fopen(argv[2], "r");
    if (!address_file)
    {
        fprintf(stderr, "Address file at '%s' could not be opened", argv[2]);
        exit(4);
    }

    physical_memory = (signed char *)malloc(NUMBER_OF_FRAMES * FRAME_SIZE);

    for (int i = 0; i < NUMBER_OF_FRAMES; i++)
    {
        free_frame_list[i] = i;
        page_table[i] = -1; // Unused entry is -1
    }

    for (int i = 0; i < TLB_SIZE; i++)
    {
        tlb[i].valid = 0;
    }

    unsigned int page_fault_cnt = 0, tlb_hit_cnt = 0;

    while (fgets(buffer, BUFFER_SIZE, address_file))
    {
        unsigned int logical_address;
        sscanf(buffer, "%u", &logical_address);

        unsigned short page_number = (logical_address >> 8) & 0xFF;
        unsigned short offset = logical_address & 0xFF;
        unsigned short frame_number = 0;
        int tlb_index = -1;

        for (int i = 0; i < TLB_SIZE; i++)
        {
            tlb_usage_priority[i]++;
            if (tlb[i].valid && tlb[i].page_number == page_number)
            {
                frame_number = tlb[i].frame_number;
                tlb_index = i;
                tlb_usage_priority[i] = 0;
                tlb_hit_cnt++;
            }
        }

        if (frame_number)
        {
            ;
        }
        // Need to get a frame from backing store
        else if (page_table[page_number] == -1)
        {
            int i = 0;
            while (free_frame_list[i] == -1)
            {
                i++;
            }

            frame_number = free_frame_list[i];
            free_frame_list[i] = -1;
            page_table[page_number] = frame_number;

            fseek(backing_store, page_number * FRAME_SIZE, SEEK_SET);
            fread(physical_memory + (frame_number * FRAME_SIZE), sizeof(signed char), FRAME_SIZE, backing_store);

            page_fault_cnt++;

            int free_tlb_index = -1;

            for (int j = 0; j < TLB_SIZE; j++)
            {
                if (!tlb[j].valid)
                {
                    tlb[j].valid = 1;
                    free_tlb_index = j;
                    break;
                }
            }

            if (free_tlb_index == -1)
            {
                int largest_tlb_history = 0, largest_tlb_history_index = -1;
                for (int j = 0; j < TLB_SIZE; j++)
                {
                    if (largest_tlb_history < tlb_usage_priority[j])
                    {
                        largest_tlb_history = tlb_usage_priority[j];
                        largest_tlb_history_index = j;
                    }
                }

                tlb[largest_tlb_history_index].frame_number = frame_number;
                tlb[largest_tlb_history_index].page_number = page_number;
                tlb_usage_priority[largest_tlb_history_index] = 0;
            }
            else
            {
                tlb[free_tlb_index].page_number = page_number;
                tlb[free_tlb_index].frame_number = frame_number;
            }
        }
        else
        {
            frame_number = page_table[page_number];
        }

        unsigned short physical_address = (frame_number * FRAME_SIZE) + offset;

        printf("Virtual address: %u Physical address: %u Value: %d\n", logical_address, physical_address, physical_memory[physical_address]);
    }

    fclose(backing_store);
    fclose(address_file);

    printf("Page fautls = %d\nTLB Hits = %d\n", page_fault_cnt, tlb_hit_cnt);
}
