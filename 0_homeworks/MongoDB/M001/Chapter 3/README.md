# Chapter 3: Deeper Dive on the MongoDB Query Language
## Challenge Problem: Single Value in an Array of Integers
Query:
``` {"results": {$elemMatch: {$gte: 70, $lt: 80} }} ```

Answer:
``` 744 ```