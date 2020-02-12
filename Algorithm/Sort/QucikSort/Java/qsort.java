import java.io.*;
import java.util.*;
import java.math.*;

public class Main {
	
	public static void main(String[] args) {
		//FS cin = new FS(System.in);
		Scanner cin = new Scanner(new BufferedInputStream(System.in));
		PrintWriter cout = new PrintWriter(System.out);
		while(cin.hasNext()) {
			int n = cin.nextInt();
			int [] a = new int [100];
			for(int i = 0; i < n; i++) {
				a[i] = cin.nextInt();
			}
			qsort(a, 0, n-1);
			for(int i = 0; i < n; i++) {
				cout.printf("%d ", a[i]);
			}
			cout.println();
		}
		cin.close();
		cout.close();
	}
	
	private static void qsort(int [] a, int l, int r) {
		if(l >= r) return;
		int i = l, j = r;
		int mid = a[l];
		while(i < j) {
			while(a[j] >= mid && i < j) j--;
			a[i] = a[j];
			while(a[i] <= mid && i < j) i++;
			a[j] = a[i];
		}
		a[i] = mid;
		qsort(a, l, i-1);
		qsort(a, i+1, r);
	}
	
	private static class FS {
		
        BufferedReader br;
        StringTokenizer st;
        
        public FS(InputStream in) {
            br = new BufferedReader(new InputStreamReader(in));
        }
        
        String next(){
            while(st==null||!st.hasMoreElements()){
                try{st = new StringTokenizer(br.readLine());}
                catch(IOException e){e.printStackTrace();}
            }
            return st.nextToken();
        }
        int nextInt() {return Integer.parseInt(next());}
        long nextLong() {return Long.parseLong(next());}
        double nextDouble() { return Double.parseDouble(next());}
    }
	
}