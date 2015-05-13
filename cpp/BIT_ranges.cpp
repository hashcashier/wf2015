//Point update, Range query
void updatePoint(int idx, int val) {
	update(idx, val);
}

int queryRange(int a, int b) {
	return query(b) - query(a - 1);
}

//Range update, Point query
void updateRange(int a, int b, int val) {
	update(a, val);
	update(b+1, -val);
}

int queryPoint(int idx) {
	return query(idx);
}

//Range update, Range query
void updateRange(int a, int b, int val) {
	update(firstBIT, a, val);
	update(firstBIT, b+1, -val);
	update(secondBIT, a, val*(a-1));
	update(secondBIT, b+1, -val*b);
}

int sum(int idx) {
	return query(firstBIT, idx)*idx - query(secondBIT, idx);
}

int queryRange(int a, int b) {
	return sum(b) - sum(a - 1);
}