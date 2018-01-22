extern long hash_key(int key){
   int s = 2654435769;
   int r0 = s * key;
   return (r0 >> 18);
}
