#include <cstdio>
#include <cstring>

#include <vector>
#include <algorithm>

using namespace std;
typedef long long llint;
const int off = ( 1 << 17 );

#define MAX 100005
#define mid ( ( x + y ) >> 1 )
#define L(x) ( ( x ) << ( 1 ) )
#define R(x) ( L( x ) | ( 1 ) )

int T;
int d[ MAX ];
int m[ MAX ];
int f[ MAX ];
int r[ MAX ];

llint p[ off << 1 ];
llint t[ off << 1 ];
llint s[ off << 1 ];
int lo, hi;

bool cmpf( int a, int b ) {
  return ( d[a] < d[b] );
}

void push( int n ) {
  t[L(n)] += p[n]; p[L(n)] += p[n];
  t[R(n)] += p[n]; p[R(n)] += p[n];
  p[n] = 0;
}

void _set( int x, int y, int n, llint val ) {
  if( x >= hi || y <= lo ) return;
  if( x >= lo && y <= hi ) {
    t[n] = val;
    return;
  }
  push( n );
  _set( x, mid, L(n), val );
  _set( mid, y, R(n), val );
  t[n] = max( t[L(n)], t[R(n)] );
}

void _add( int x, int y, int n, llint val ) {
  if( x >= hi || y <= lo ) return;
  if( x >= lo && y <= hi ) {
    t[n] += val;
    p[n] += val;
    return;
  }
  push( n );
  _add( x, mid, L(n), val );
  _add( mid, y, R(n), val );
  t[n] = max( t[L(n)], t[R(n)] );
}

llint _sum( int x, int y, int n ) {
  if( x >= hi || y <= lo ) return 0;
  if( x >= lo && y <= hi ) return s[n];
  return _sum( x, mid, L(n) ) +_sum( mid, y, R(n) );
}

void put( int pos, llint val ) {
  pos += off; s[pos] = val;
  for( pos >>= 1; pos; pos >>= 1 )
    s[pos] = s[L(pos)]+s[R(pos)];
}

void set( int pos, llint val ) {
  lo = pos; hi = pos+1;
  _set( 0, off, 1, val );
}

void add( int x, int y, llint val ) {
  lo = x; hi = y+1;
  _add( 0, off, 1, val );
}

llint sum( int pos ) {
  lo = 0; hi = pos+1;
  _sum( 0, off, 1 );
}

int main( void )
{
  scanf( "%d", &T );

  for( int i = 0; i < T; ++i ) {
    scanf( "%d%d", d+i, m+i );
    f[i] = i;
  }

  sort( f, f + T, cmpf );
  for( int i = 0; i < T; ++i ) 
    r[f[i]] = i;

  for( int i = 0; i < ( off << 1 ); ++i )
    t[i] = -1000000000000000000LL;

  for( int i = 0; i < T; ++i ) {
    set( r[i], sum( r[i] )+m[i]-d[i] );
    add( r[i]+1, T-1, m[i] );
    put( r[i], m[i] );
    printf( "%lld\n", max( 0LL, t[1] ) );
  }

  return 0;
}