; ModuleID = 'isprime'
source_filename = "isprime"

@n = global i64 0
@i = global i64 0
@prime = global i1 false

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
  %n.val = load i64, ptr @n, align 4
  %lttmp = icmp slt i64 %n.val, 2
  br i1 %lttmp, label %then, label %else

then:                                             ; preds = %entry
  store i1 false, ptr @prime, align 1
  br label %ifend

else:                                             ; preds = %entry
  store i1 true, ptr @prime, align 1
  store i64 2, ptr @i, align 4
  br label %while.cond

ifend:                                            ; preds = %while.end, %then
  %prime.val = load i1, ptr @prime, align 1
  call void @mp_write_bool(i1 %prime.val)
  call void @mp_writeln()
  ret i32 0

while.cond:                                       ; preds = %ifend6, %else
  %i.val = load i64, ptr @i, align 4
  %i.val1 = load i64, ptr @i, align 4
  %multmp = mul i64 %i.val, %i.val1
  %n.val2 = load i64, ptr @n, align 4
  %letmp = icmp sle i64 %multmp, %n.val2
  br i1 %letmp, label %while.body, label %while.end

while.body:                                       ; preds = %while.cond
  %n.val3 = load i64, ptr @n, align 4
  %i.val4 = load i64, ptr @i, align 4
  %modtmp = srem i64 %n.val3, %i.val4
  %eqtmp = icmp eq i64 %modtmp, 0
  br i1 %eqtmp, label %then5, label %ifend6

while.end:                                        ; preds = %while.cond
  br label %ifend

then5:                                            ; preds = %while.body
  store i1 false, ptr @prime, align 1
  %n.val7 = load i64, ptr @n, align 4
  store i64 %n.val7, ptr @i, align 4
  br label %ifend6

ifend6:                                           ; preds = %then5, %while.body
  %i.val8 = load i64, ptr @i, align 4
  %addtmp = add i64 %i.val8, 1
  store i64 %addtmp, ptr @i, align 4
  br label %while.cond
}
