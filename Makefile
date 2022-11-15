binary_tree: binary_tree.c
	cc -Wall -g -o $@ $<

linked_list: linked_list.c
	cc -Wall -g -o $@ $<

doubly_linked_list: doubly_linked_list.c
	cc -Wall -g -o $@ $<

gap_buffer: gap_buffer.c
	cc -Wall -g -o $@ $<

clean:
	rm -f binary_tree linked_list doubly_linked_list gap_buffer
