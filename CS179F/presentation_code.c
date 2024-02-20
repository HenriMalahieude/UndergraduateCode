struct address_space *folio_mapping(struct folio *folio)
{
	struct address_space *mapping;

    //...

	mapping = folio->mapping;

	//...

	return mapping;
}



bool folio_mark_dirty(struct folio *folio)
{
	struct address_space *mapping = folio_mapping(folio);

	//...
}



bool set_page_dirty(struct page *page)
{
	return folio_mark_dirty(page_folio(page));
}



void rds_atomic_free_op(struct rm_atomic_op *ao)
{
	struct page *page = sg_page(ao->op_sg);

	set_page_dirty(page);
	put_page(page);

	kfree(ao->op_notifier);
	ao->op_notifier = NULL;
	ao->op_active = 0;
}



static void rds_message_purge(struct rds_message *rm)
{
	//...

	if (rm->atomic.op_active) 
		rds_atomic_free_op(&rm->atomic);
	
	//...
}


void rds_message_put(struct rds_message *rm)
{
	//...
	if (/*. . .*/) {
		//...
		rds_message_purge(rm);

		kfree(rm);
	}
}



int rds_cmsg_atomic(struct rds_sock *rs, struct rds_message *rm,
		    struct cmsghdr *cmsg)
{
	struct page *page = NULL;
	//...

	rm->atomic.op_sg = rds_message_alloc_sgs(rm, 1);
	//...

	/* verify 8 byte-aligned */
	if (args->local_addr & 0x7) {
		ret = -EFAULT;
		goto err;
	}

	ret = rds_pin_pages(args->local_addr, 1, &page, 1);
	//goto err;

	sg_set_page(rm->atomic.op_sg, page, 8, offset_in_page(args->local_addr));

	//....
	return ret;
err:
	if (page) put_page(page);
	//rm->atomic.op_active = 0
	kfree(rm->atomic.op_notifier);

	return ret;
}



static int rds_cmsg_send(struct rds_sock *rs, struct rds_message *rm,
			 struct msghdr *msg, int *allocated_mr)
{
	struct cmsghdr *cmsg;
	int ret = 0;

	for_each_cmsghdr(cmsg, msg) {
		//...
		switch (cmsg->cmsg_type) {
		//...
		case RDS_CMSG_MASKED_ATOMIC_FADD:
			ret = rds_cmsg_atomic(rs, rm, cmsg);
		//...
		}

		//...
	}

	return ret;
}

int rds_sendmsg(struct socket *sock, struct msghdr *msg, size_t payload_len)
{
	//...

	/* Parse any control messages the user may have included. */
	ret = rds_cmsg_send(rs, rm, msg, &allocated_mr);

	//...

	//goto out;

	//...

	rds_message_put(rm);
	return payload_len;
out:
	//...

	if (rm)
		rds_message_put(rm);
	return ret;
}