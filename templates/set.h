
#define __problem__ 1
#define CATEGORY___nist-level__ 1
#define __target__ 1

/* skip asserts so that verify() always returns a value */
#define SKIP_ASSERT

#if defined(SPEED)
#define NO_TREES 1
#else
#undef NO_TREES
#endif

