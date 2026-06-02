; ModuleID = 'fibonacci'
source_filename = "fibonacci"

@n = global i64 0
@a = global i64 0
@b = global i64 0
@i = global i64 0
@next = global i64 0

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
  %i.limit = alloca i64, align 8
  %argc64 = sext i32 %argc to i64
  call void @mp_init_runtime(i64 %argc64, ptr %argv)
  %0 = call i64 @mp_argi(i64 1)
  store i64 %0, ptr @n, align 4
  %n.val = load i64, ptr @n, align 4
  %letmp = icmp sle i64 %n.val, 0
  br i1 %letmp, label %then, label %else

then:                                             ; preds = %entry
  call void @mp_write_int(i64 0)
  call void @mp_writeln()
  br label %ifend

else:                                             ; preds = %entry
  store i64 0, ptr @a, align 4
  store i64 1, ptr @b, align 4
  %n.val1 = load i64, ptr @n, align 4
  %subtmp = sub i64 %n.val1, 1
  store i64 1, ptr @i, align 4
  store i64 %subtmp, ptr %i.limit, align 4
  br label %for.cond

ifend:                                            ; preds = %for.end, %then
  ret i32 0

for.cond:                                         ; preds = %for.step, %else
  %i.cur = load i64, ptr @i, align 4
  %i.limitv = load i64, ptr %i.limit, align 4
  %forcond = icmp sle i64 %i.cur, %i.limitv
  br i1 %forcond, label %for.body, label %for.end

for.body:                                         ; preds = %for.cond
  %a.val = load i64, ptr @a, align 4
  %b.val = load i64, ptr @b, align 4
  %addtmp = add i64 %a.val, %b.val
  store i64 %addtmp, ptr @next, align 4
  %b.val2 = load i64, ptr @b, align 4
  store i64 %b.val2, ptr @a, align 4
  %next.val = load i64, ptr @next, align 4
  store i64 %next.val, ptr @b, align 4
  br label %for.step

for.step:                                         ; preds = %for.body
  %i.stepv = load i64, ptr @i, align 4
  %fornext = add i64 %i.stepv, 1
  store i64 %fornext, ptr @i, align 4
  br label %for.cond

for.end:                                          ; preds = %for.cond
  %b.val3 = load i64, ptr @b, align 4
  call void @mp_write_int(i64 %b.val3)
  call void @mp_writeln()
  br label %ifend
}
