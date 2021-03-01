2-13:  
how to set cache clusivity?  
i'using ruby cache, not classic cache. In memtest.py, there are some code about clusivity, these code can be use in ruby cache?
```
# memtest.py

# Now add additional cache levels (if any) by scaling L1 params, the
# first element is Ln, and the last element L1
for scale in cachespec[:-1]:
     # Clone previous level and update params
     prev = cache_proto[0]
     next = prev()
     next.size = prev.size * scale
     next.tag_latency = prev.tag_latency * 10
     next.data_latency = prev.data_latency * 10
     next.response_latency = prev.response_latency * 10
     next.assoc = prev.assoc * scale
     next.mshrs = prev.mshrs * scale

     # Swap the inclusivity/exclusivity at each level. L2 is mostly
     # exclusive with respect to L1, L3 mostly inclusive, L4 mostly
     # exclusive etc.
     next.writeback_clean = not prev.writeback_clean
     if (prev.clusivity.value == 'mostly_incl'):
          next.clusivity = 'mostly_excl'
     else:
          next.clusivity = 'mostly_incl'
```
