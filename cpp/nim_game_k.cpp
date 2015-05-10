ii nim(vi &H, bool misere, int K, int R) {
	int sum = 0;
	for(int i = 0; i < H.size(); i++)
		sum += XOR(R?H[i]%(R+1):H[i],K+1);
	/*The winning strategy is to move such that this sum is zero for every digit. Indeed, the value thus computed is zero for the final position, and given a configuration of heaps for which this value is zero, any change of at most k heaps will make the value non-zero. Conversely, given a configuration with non-zero value, one can always take from at most k heaps, carefully chosen, so that the value will become zero.*/
}