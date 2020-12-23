static void
bstack(Monitor *m) {
	int x, y, h, w, mh;
	unsigned int i, n;
	Client *c;

	for(n = 0, c = nexttiled(m->clients); c; c = nexttiled(c->next), n++);
	if(n == 0)
		return;
	/* master */
	c = nexttiled(m->clients);
	mh = m->mfact * m->wh;
	resize(c, m->wx + m->gappx, m->wy + m->gappx, m->ww - 2 * c->bw - 2 * m->gappx, (n == 1 ? m->wh : mh) - 2 * c->bw - 2 * m->gappx, False);
	if(--n == 0)
		return;
	/* tile stack */
	x = m->wx + m->gappx;
	y = (m->wy + mh > c->y + c->h) ? c->y + c->h + 2 * c->bw + m->gappx : m->wy + mh + m->gappx;
	w = m->ww / n;
	h = (m->wy + mh > c->y + c->h) ? m->wy + m->wh - y - m->gappx : m->wh - mh - m->gappx;
	if(w < bh)
		w = m->ww - 2 * m->gappx;
	for(i = 0, c = nexttiled(c->next); c; c = nexttiled(c->next), i++) {
		resize(c, (i == 0) ? x : x + m->gappx, y, /* remainder */ ((i + 1 == n)
		       ? m->wx + m->ww - x - 2 * c->bw - 2 * m->gappx : w - 2 * c->bw - m->gappx), h - 2 * c->bw, False);
		if(w != m->ww)
			x = c->x + WIDTH(c);
	}
}
