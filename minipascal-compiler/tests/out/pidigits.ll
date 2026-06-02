; ModuleID = 'pidigits'
source_filename = "pidigits"

@n = global i64 0
@i = global i64 0
@scale = global i64 0
@terms = global i64 0
@sign = global i64 0
@denom = global i64 0
@piScaled = global i64 0
@termValue = global i64 0
@intPart = global i64 0
@fracPart = global i64 0
@tmp = global i64 0
@0 = private unnamed_addr constant [2 x i8] c".\00", align 1

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
  %i.limit7 = alloca i64, align 8
  %i.limit = alloca i64, align 8
  %argc64 = sext i32 %argc to i64
  call void @mp_init_runtime(i64 %argc64, ptr %argv)
  %0 = call i64 @mp_argi(i64 1)
  store i64 %0, ptr @n, align 4
  %n.val = load i64, ptr @n, align 4
  %lttmp = icmp slt i64 %n.val, 0
  br i1 %lttmp, label %then, label %ifend

then:                                             ; preds = %entry
  store i64 0, ptr @n, align 4
  br label %ifend

ifend:                                            ; preds = %then, %entry
  %n.val1 = load i64, ptr @n, align 4
  %gttmp = icmp sgt i64 %n.val1, 9
  br i1 %gttmp, label %then2, label %ifend3

then2:                                            ; preds = %ifend
  store i64 9, ptr @n, align 4
  br label %ifend3

ifend3:                                           ; preds = %then2, %ifend
  store i64 1, ptr @scale, align 4
  %n.val4 = load i64, ptr @n, align 4
  store i64 1, ptr @i, align 4
  store i64 %n.val4, ptr %i.limit, align 4
  br label %for.cond

for.cond:                                         ; preds = %for.step, %ifend3
  %i.cur = load i64, ptr @i, align 4
  %i.limitv = load i64, ptr %i.limit, align 4
  %forcond = icmp sle i64 %i.cur, %i.limitv
  br i1 %forcond, label %for.body, label %for.end

for.body:                                         ; preds = %for.cond
  %scale.val = load i64, ptr @scale, align 4
  %multmp = mul i64 %scale.val, 10
  store i64 %multmp, ptr @scale, align 4
  br label %for.step

for.step:                                         ; preds = %for.body
  %i.stepv = load i64, ptr @i, align 4
  %fornext = add i64 %i.stepv, 1
  store i64 %fornext, ptr @i, align 4
  br label %for.cond

for.end:                                          ; preds = %for.cond
  %scale.val5 = load i64, ptr @scale, align 4
  %multmp6 = mul i64 3, %scale.val5
  store i64 %multmp6, ptr @piScaled, align 4
  store i64 1, ptr @sign, align 4
  store i64 2, ptr @denom, align 4
  store i64 3000, ptr @terms, align 4
  %terms.val = load i64, ptr @terms, align 4
  store i64 1, ptr @i, align 4
  store i64 %terms.val, ptr %i.limit7, align 4
  br label %for.cond8

for.cond8:                                        ; preds = %for.step10, %for.end
  %i.cur12 = load i64, ptr @i, align 4
  %i.limitv13 = load i64, ptr %i.limit7, align 4
  %forcond14 = icmp sle i64 %i.cur12, %i.limitv13
  br i1 %forcond14, label %for.body9, label %for.end11

for.body9:                                        ; preds = %for.cond8
  %scale.val15 = load i64, ptr @scale, align 4
  %multmp16 = mul i64 4, %scale.val15
  %denom.val = load i64, ptr @denom, align 4
  %denom.val17 = load i64, ptr @denom, align 4
  %addtmp = add i64 %denom.val17, 1
  %multmp18 = mul i64 %denom.val, %addtmp
  %denom.val19 = load i64, ptr @denom, align 4
  %addtmp20 = add i64 %denom.val19, 2
  %multmp21 = mul i64 %multmp18, %addtmp20
  %divtmp = sdiv i64 %multmp16, %multmp21
  store i64 %divtmp, ptr @termValue, align 4
  %sign.val = load i64, ptr @sign, align 4
  %eqtmp = icmp eq i64 %sign.val, 1
  br i1 %eqtmp, label %then22, label %else

for.step10:                                       ; preds = %ifend23
  %i.stepv31 = load i64, ptr @i, align 4
  %fornext32 = add i64 %i.stepv31, 1
  store i64 %fornext32, ptr @i, align 4
  br label %for.cond8

for.end11:                                        ; preds = %for.cond8
  %piScaled.val33 = load i64, ptr @piScaled, align 4
  %scale.val34 = load i64, ptr @scale, align 4
  %divtmp35 = sdiv i64 %piScaled.val33, %scale.val34
  store i64 %divtmp35, ptr @intPart, align 4
  %piScaled.val36 = load i64, ptr @piScaled, align 4
  %scale.val37 = load i64, ptr @scale, align 4
  %modtmp = srem i64 %piScaled.val36, %scale.val37
  store i64 %modtmp, ptr @fracPart, align 4
  %intPart.val = load i64, ptr @intPart, align 4
  call void @mp_write_int(i64 %intPart.val)
  call void @mp_write_str(ptr @0)
  %scale.val38 = load i64, ptr @scale, align 4
  %divtmp39 = sdiv i64 %scale.val38, 10
  store i64 %divtmp39, ptr @tmp, align 4
  br label %while.cond

then22:                                           ; preds = %for.body9
  %piScaled.val = load i64, ptr @piScaled, align 4
  %termValue.val = load i64, ptr @termValue, align 4
  %addtmp24 = add i64 %piScaled.val, %termValue.val
  store i64 %addtmp24, ptr @piScaled, align 4
  br label %ifend23

else:                                             ; preds = %for.body9
  %piScaled.val25 = load i64, ptr @piScaled, align 4
  %termValue.val26 = load i64, ptr @termValue, align 4
  %subtmp = sub i64 %piScaled.val25, %termValue.val26
  store i64 %subtmp, ptr @piScaled, align 4
  br label %ifend23

ifend23:                                          ; preds = %else, %then22
  %sign.val27 = load i64, ptr @sign, align 4
  %subtmp28 = sub i64 0, %sign.val27
  store i64 %subtmp28, ptr @sign, align 4
  %denom.val29 = load i64, ptr @denom, align 4
  %addtmp30 = add i64 %denom.val29, 2
  store i64 %addtmp30, ptr @denom, align 4
  br label %for.step10

while.cond:                                       ; preds = %ifend44, %for.end11
  %tmp.val = load i64, ptr @tmp, align 4
  %gttmp40 = icmp sgt i64 %tmp.val, 0
  br i1 %gttmp40, label %while.body, label %while.end

while.body:                                       ; preds = %while.cond
  %fracPart.val = load i64, ptr @fracPart, align 4
  %tmp.val41 = load i64, ptr @tmp, align 4
  %lttmp42 = icmp slt i64 %fracPart.val, %tmp.val41
  br i1 %lttmp42, label %then43, label %ifend44

while.end:                                        ; preds = %while.cond
  %fracPart.val47 = load i64, ptr @fracPart, align 4
  call void @mp_write_int(i64 %fracPart.val47)
  call void @mp_writeln()
  ret i32 0

then43:                                           ; preds = %while.body
  call void @mp_write_int(i64 0)
  br label %ifend44

ifend44:                                          ; preds = %then43, %while.body
  %tmp.val45 = load i64, ptr @tmp, align 4
  %divtmp46 = sdiv i64 %tmp.val45, 10
  store i64 %divtmp46, ptr @tmp, align 4
  br label %while.cond
}
