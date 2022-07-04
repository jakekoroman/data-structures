binary_tree: binary_tree.c
	cc -o $@ $<

linked_list: linked_list.c
	cc -o $@ $<

doubly_linked_list: doubly_linked_list.c
	cc -o $@ $<

clean:
	rm -f binary_tree linked_list doubly_linked_list
