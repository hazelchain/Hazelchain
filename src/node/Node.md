# Node

- all characters in strings and as singular characters, are encoded to UTF-16, not ASCII

## Format

```
*hexadecimal*
01 00 00 00 00 00 00 00 06 00 00 00 68 65 6c 6c 6f 21 00 00 00 00
└────┬────┘ └────┬────┘ └────┬────┘ └─────────────┬─────────────┘
     A           B           C                    D
```

<ol type="A">
    <li>4 bytes (unsigned int): node version, regarding cross contamination</li>
    <li>4 bytes (unsigned int): id of packet</li>
    <li>4 bytes (unsigned int): size of data in bytes, not including the header</li> 
    <li>The rest is the expected data of the packet type</li>
</ol>

### Formatting Rules

- All characters must be encoded in UTF-16 and must be in little endian form.
- Any strings must be escaped with 4 bytes of 0s