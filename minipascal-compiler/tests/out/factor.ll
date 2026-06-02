; ModuleID = 'factor'
source_filename = "factor"

@n = global i64 0
@d = global i64 0
@0 = private unnamed_addr constant [2 x i8] c" \00", align 1

declare void @mp_init_runtime(i64, ptr)

declare i64 @mp_argc()

declare i64 @mp_argi(i64)

declare void @mp_write_int(i64)

declare void @mp_writeln_int(i64)

declare void @mp_write_bool(i1)

declare void @mp_writeln_bool(i1)

declare void @mp_write_str(ptr)

declare void @mp_writeln()

define i32 @main(i32 %argc, ptr %argv) {
entry:
  %argc64 = sext i32 %argc to i64
  call void @mp_init_runtime(i64 %argc64, ptr %argv)
  %0 = call i64 @mp_argi(i64 1)
  store i64 %0, ptr @n, align 4
  store i64 2, ptr @d, align 4
  br label %while.cond

while.cond:                                       ; preds = %while.end4, %entry
  %d.val = load i64, ptr @d, align 4
  %d.val1 = load i64, ptr @d, align 4
  %multmp = mul i64 %d.val, %d.val1
  %n.val = load i64, ptr @n, align 4
  %letmp = icmp sle i64 %multmp, %n.val
  br i1 %letmp, label %while.body, label %while.end

while.body:                                       ; preds = %while.cond
  br label %while.cond2

while.end:                                        ; preds = %while.cond
  %n.val11 = load i64, ptr @n, align 4
  %gttmp = icmp sgt i64 %n.val11, 1
  br i1 %gttmp, label %then, label %else

while.cond2:                                      ; preds = %while.body3, %while.body
  %n.val5 = load i64, ptr @n, align 4
  %d.val6 = load i64, ptr @d, align 4
  %modtmp = srem i64 %n.val5, %d.val6
  %eqtmp = icmp eq i64 %modtmp, 0
  br i1 %eqtmp, label %while.body3, label %while.end4

while.body3:                                      ; preds = %while.cond2
  %d.val7 = load i64, ptr @d, align 4
  call void @mp_write_int(i64 %d.val7)
  call void @mp_write_str(ptr @0)
  %n.val8 = load i64, ptr @n, align 4
  %d.val9 = load i64, ptr @d, align 4
  %divtmp = sdiv i64 %n.val8, %d.val9
  store i64 %divtmp, ptr @n, align 4
  br label %while.cond2

while.end4:                                       ; preds = %while.cond2
  %d.val10 = load i64, ptr @d, align 4
  %addtmp = add i64 %d.val10, 1
  store i64 %addtmp, ptr @d, align 4
  br label %while.cond

then:                                             ; preds = %while.end
  %n.val12 = load i64, ptr @n, align 4
  call void @mp_write_int(i64 %n.val12)
  call void @mp_writeln()
  br label %ifend

else:                                             ; preds = %while.end
  call void @mp_writeln()
  br label %ifend

ifend:                                            ; preds = %else, %then
  ret i32 0
}
