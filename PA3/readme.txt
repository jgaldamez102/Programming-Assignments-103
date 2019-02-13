Prelab: 
1. a) 265x265, since youll need to pad with N/2 rows/columns on both sides 
      to support the largest possible kernel, which would be 11x11.
   b) image[N/2][N/2][], or row = N/2, and col = N/2
   c) row=col= (size of padded image - (N/2)).
2. Not normalizing brings up the brightness significiantly to the image. 
    .1020 .1153 .1020 
    .1153 .1303 .1153
    .1020 .1153 .1020

Experimentation:

1. a) varying sigma, specifically increasing, the image blurs to a certain
      extent and the values from the Gaussian begin to stay in the same
      similar range. blurring decreases incresingly going closer to 
      sigma =0, where it displays a black photo.
   b) as N increasing, the image isnt affected as much and stays at a 
      certain blurriness threshold, but it does increase as N increases.
2. It has a negative affect, almost like an inverse, but it really also 
    sharpens the image. 
3. Attempting to sharpen a blurred image doesnt really give you the original
   as you aren't really doing the inverse operations of blur to sharpen the
   image, but rather you subtract the original with the blurred image itself.
   the equations and procedure to do both are different as well, such as 
   using the gaussian equation to blur, but manipulating sharp to thatblurred
   image will cause different images to be made. They are not inverses.
4. O(n^2)
