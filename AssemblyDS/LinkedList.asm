INCLUDE Irvine32.inc
INCLUDE Macros.inc

insert PROTO, data:DWORD
delete PROTO, key:DWORD

node STRUCT
    data        DWORD   ?
    next        DWORD   ?
node ENDS

.data
    headPtr     DWORD 0
    tmpPtr      DWORD 0
    dataSegment DWORD ?
.code
main PROC   
    mov dataSegment, OFFSET dataSegment + TYPE DWORD + 12   ; 12 for other variable

    invoke insert, 10      
    invoke insert, 20
    invoke insert, 30
    
    ;invoke delete, 10
    ;invoke delete, 20
    ;invoke delete, 30
    
    ;invoke insert, 10
    
    call print
    exit
main ENDP

print PROC
    mov esi, headPtr 
    .WHILE esi != 0
        mov eax, [esi].node.data
        call WriteInt
        call Crlf
        
        mov esi, [esi].node.next
    .ENDW    
    ret
print ENDP

insert PROC, data:DWORD
    .IF headPtr == 0
        mov esi, dataSegment
        mov headPtr, esi
        ; headPtr = dataSegment
        
        mov eax, data
        mov [esi].node.data, eax   
        ; head.data = data

        mov [esi].node.next, 0
        ; head.next = 0
    .ELSE
        add dataSegment, TYPE node ; Get space

        mov esi, dataSegment
        
        mov eax, data
        mov [esi].node.data, eax
        ; node.data = data
        
        mov eax, headPtr
        mov [esi].node.next, eax 
        ; node.next = headPtr
        
        mov headPtr, esi
        ; headPtr = node
    .ENDIF   
    ret
insert ENDP

delete PROC, key:DWORD
    LOCAL history:DWORD
    mov history, 0
    
    mov esi, headPtr
    .WHILE esi != 0
        mov eax, [esi].node.data
        .IF eax == key
            .IF history == 0
                mov eax, [esi].node.next
                mov headPtr, eax
            .ELSE
                mov eax, [esi].node.next        ; Pointer to previous  
                mov esi, history
                mov [esi].node.next, eax                
            .ENDIF
            ret
        .ELSE
            mov history,esi 
            mov esi, [esi].node.next
        .ENDIF
    .ENDW 
delete ENDP
END main