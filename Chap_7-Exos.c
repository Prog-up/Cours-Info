int Delannay(int i, int j){
    if (i != 0 && j != 0) {
        return Delannay(i, j-1)+Delannay(i-1,j)+Delannay(i-1,j-1);
    } else if (i = 0 || j = 0){
        return 1;
    }
}